#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#define keyboard_size 4
#define switch_size 4
#define keycode_size 6

static uint32_t switch_pins[switch_size];

struct keyboard
{
    uint8_t button_name;
    uint32_t button_pin;
    bool button_state;
    uint8_t keycode[keycode_size];
};

// modes 
extern uint8_t windows [keyboard_size][keycode_size];
extern uint8_t vscode [keyboard_size][keycode_size];

// functions
void keyboard_init();
uint32_t button_state();
uint8_t set_keycode(uint8_t, uint8_t);   
uint16_t read_mode();

#endif