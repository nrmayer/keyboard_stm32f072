#include "matrix.h"

// memset
#include <string.h>

#include "usbd_conf.h"
#include "usb.h"

#include "config.h"

#define DEVICE_KEYCODE_REPORT_SIZE (USBD_CUSTOMHID_OUTREPORT_BUF_SIZE - 2)

static int current_layer = 0;
static int base_layer = 0;

typedef struct KeyNode {
    const KeyFunction* key;

    struct KeyNode* next;
    struct KeyNode* prev;
} KeyNode;

typedef struct MatrixNode {
    KeyNode* keynode;
    const KeyFunction* keyfunc;
} MatrixNode;

// keycode literals list

static KeyNode keynode_list[DEVICE_KEYCODE_REPORT_SIZE];

static KeyNode* keynode_list_head = NULL;
static KeyNode* keynode_list_tail = NULL;

static KeyNode* keynode_list_unused;

// matrix states

static MatrixNode matrix_pin_states[ROW_PINS_NUM][COL_PINS_NUM];

// HID buffer

__ALIGN_BEGIN static struct __ALIGN_END {
    uint8_t modifiers;
    uint8_t RESERVED;
    uint8_t keycodes[DEVICE_KEYCODE_REPORT_SIZE];
} usb_hid_buffer;


// =======================================
// =======================================


static void remove_keyliteral_node(KeyNode** node_ptr) {
    KeyNode* node = *node_ptr;
    if (!node) return;

    // remove node from list

    // move head/tail
    if (keynode_list_head == node) 
        keynode_list_head = node->next;
    if (keynode_list_tail == node) 
        keynode_list_tail = node->prev;

    // join neighbors
    if (node->prev) 
        node->prev->next = node->next;
    if (node->next) 
        node->next->prev = node->prev;

    // set as first element of unused list
    node->next = keynode_list_unused;
    keynode_list_unused = node;
    // both prev vals left as junk (never used uninited)
}

static void remove_layerswitch_hold(KeyNode** node_ptr) {
    // just remove all layers
    current_layer = base_layer;
}

static void remove_modifier_mask(MatrixNode* node_ptr) {
    // bit XOR takes it out
    usb_hid_buffer.modifiers = usb_hid_buffer.modifiers ^ node_ptr->keyfunc->value;
}

static void key_remove(MatrixNode* node_ptr) {
    switch(node_ptr->keyfunc->function) {
        case KeyLiteral: 
            remove_keyliteral_node(&node_ptr->keynode);
            break;
        case LayerSwitchHold: 
            remove_layerswitch_hold(&node_ptr->keynode);
            break;
        case ModifierMask:
            remove_modifier_mask(node_ptr);
            break;
        default: break;
    }

    // remove key from matrix
    memset(node_ptr, 0, sizeof(MatrixNode));
}


static void add_keyliteral_node(KeyNode** node_ptr, const KeyFunction* key_function) {
    // key turning on, add to keycode if possible

    // check if linked list is full
    if (!keynode_list_unused) 
        return;

    // add to list
    
    // get next unused node
    KeyNode* node = keynode_list_unused;
    keynode_list_unused = node->next;
    node->next = NULL;

    // append node to linkedlist
    if (keynode_list_tail) {
        keynode_list_tail->next = node;
        node->prev = keynode_list_tail;
    } else {
        // only node, set as head as well as tail
        keynode_list_head = node;
        node->prev = NULL;
    }
    keynode_list_tail = node;

    // set node data
    node->key = key_function;

    // put node in matrix state array
    *node_ptr = node;
}

static void add_layerswitch_hold(KeyNode** node_ptr, const KeyFunction* key_function) {
    // only one at a time, will override if new one pressed
    current_layer = key_function->value;
}

static void add_modifier_mask(MatrixNode* node_ptr) {
    // bitwise OR adds to it
    usb_hid_buffer.modifiers = usb_hid_buffer.modifiers | node_ptr->keyfunc->value;
}

static void key_add(MatrixNode* node_ptr, const KeyFunction* key_function) {
    // set key function of matrix value
    node_ptr->keyfunc = key_function;

    // handle according to type
    switch (key_function->function) {
        case KeyLiteral:
            add_keyliteral_node(&node_ptr->keynode, key_function);
            break;
        case LayerSwitchHold:
            add_layerswitch_hold(&node_ptr->keynode, key_function);
            break;
        case ModifierMask:
            add_modifier_mask(node_ptr);
            break;
        default: break;
    }
}


static void update_hid_buffer() {
    // modifier mask updated with their respective functions
    
    // update keys pressed
    KeyNode* curr = keynode_list_head;
    for (int i = 0; i < DEVICE_KEYCODE_REPORT_SIZE; ++i) {
        if (!curr) {
            usb_hid_buffer.keycodes[i] = 0;
            continue;
        }
        // will only be nodes with .function = KeyLiteral 
        usb_hid_buffer.keycodes[i] = curr->key->value;
        curr = curr->next;
    }
}


void start_matrix_scan() {
    // setup linked list
    for (int i = 0; i < DEVICE_KEYCODE_REPORT_SIZE - 1; ++i) {
        // prev not needed (not used on uninited nodes)
        keynode_list[i].next = &keynode_list[i+1];
    }
    keynode_list_unused = &keynode_list[0];

    // TODO timer approach
    for (;;) { update_matrix(); }
}

void update_matrix() {
    int changed = 0;
    
    for (int col = 0; col <  COL_PINS_NUM; ++col) {
        // write COL high
        HAL_GPIO_WritePin(COL_PINS[col].letter, COL_PINS[col].num, 1);
        
        for (int row = 0; row < ROW_PINS_NUM; ++row) {
            // read ROW to see if COL high comes through
            int pin_state = HAL_GPIO_ReadPin(ROW_PINS[row].letter, ROW_PINS[row].num);

            MatrixNode matrix_state = matrix_pin_states[row][col];

            // check if keystate changed
            if (!pin_state && !matrix_state.keyfunc) continue;
            if (pin_state && matrix_state.keyfunc) continue;

            // changed, add/remove from report
            if (pin_state) { 
                key_add(&matrix_pin_states[row][col], &KEYBOARD_DEFS[current_layer][row][col]);
            }
            else key_remove(&matrix_pin_states[row][col]);

            changed = 1;
        }

        // write COL back low (has pulldown resistors)
        HAL_GPIO_WritePin(COL_PINS[col].letter, COL_PINS[col].num, 0);
    }

    // TODO handle thumbpad

    if (changed) {
        // update buffer from keynode list
        update_hid_buffer();
        // send USB update
        usb_hid_send_buffer((uint8_t*)&usb_hid_buffer, USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
    }
}