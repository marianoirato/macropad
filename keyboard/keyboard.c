#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include "keyboard.h"
#include "usb_descriptors.h"
#include "oled.h"
//#include "binds.h"

struct keyboard keyboard[keyboard_size];

static uint32_t switch_pins[switch_size] = {10, 11, 12, 13};

//Modes 
uint8_t windows [keyboard_size][keycode_size] =
{
    // {HID_KEY_CONTROL_LEFT, HID_KEY_T}, //button a
    // {HID_KEY_CONTROL_LEFT, HID_KEY_W}, //button b
    // {HID_KEY_CONTROL_LEFT, HID_KEY_E}, //button c
    // {HID_KEY_CONTROL_LEFT, HID_KEY_A}  //button d
    {HID_KEY_A},
    {HID_KEY_B},
    {HID_KEY_C},
    {HID_KEY_D}
};

uint8_t vscode [keyboard_size][keycode_size] =
{
    {HID_KEY_CONTROL_LEFT, HID_KEY_W}, //button a
    {HID_KEY_CONTROL_LEFT, HID_KEY_W}, //button b
    {HID_KEY_CONTROL_LEFT, HID_KEY_W}, //button c
    {HID_KEY_CONTROL_LEFT, HID_KEY_W}  //button d
};

void keyboard_init()
{
    for(int i = 0; i < keyboard_size; i++)
    {
        // Create the struct
        keyboard[i].button_name = 'a' + i;
        keyboard[i].button_pin = 2 + i;
        // Initialize the buttons GPIO
        gpio_init(keyboard[i].button_pin);
        gpio_set_dir(keyboard[i].button_pin, GPIO_OUT);
        gpio_pull_down(keyboard[i].button_pin);         // When pressed button = HIGH, else button = LOW  
    }

    // Initialize switch for mode
    for(int i = 0; i < switch_size; i++)
    {
        gpio_init(switch_pins[i]);
        gpio_set_dir(switch_pins[i], GPIO_IN);
        gpio_pull_down(switch_pins[i]);
    }
}

uint32_t button_state()
{
    uint8_t state;

    for(int i = 0; i < keyboard_size; i++) 
    { 
        //Read button state
        keyboard[i].button_state = gpio_get(keyboard[i].button_pin);

        //If the button is pressed, then return 1
        if(keyboard[i].button_state == 1)
            return keyboard[i].button_name;
    }

    return 0;
}

uint8_t set_keycode(uint8_t button_pressed, uint8_t i)
{
    uint16_t mode = read_mode();

    switch (mode)
    {
        case 0: // windows mode            
            for(int i = 0; i < keyboard_size;i++)
            {
                for(int j = 0; j < keycode_size; j++)
                {
                    keyboard[i].keycode[j] = windows[i][j];
                }
            }
            break;
        case 1: // vscode mode            
            for(int i = 0; i < keyboard_size;i++)
            {
                for(int j = 0; j < keycode_size; j++)
                {
                    keyboard[i].keycode[j] = vscode[i][j];
                }
            }            
            break;
        default: // windows mode
            for(int i = 0; i < keyboard_size;i++)
            {
                for(int j = 0; j < keycode_size; j++)
                {
                    keyboard[i].keycode[j] = windows[i][j];
                }
            }
            break;
    }

    return keyboard[button_pressed - 97].keycode[i];
}

uint16_t read_mode()
{
    uint16_t mode;
    uint16_t counter;

    for(int i = 0; i < switch_size; i++)
    {
        if(gpio_get(switch_pins[i]) == 1)
        {
            counter = pow(2, i);
            mode += counter;  
        }    
    }

    return mode;      
}