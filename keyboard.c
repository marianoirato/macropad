#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include "keyboard.h"
#include "usb_descriptors.h"

struct keyboard keyboard[keyboard_size];

static uint32_t switch_pins[switch_size] = {10, 11, 12, 13};

//Modes 
uint8_t windows [keyboard_size][keycode_size] =
{
    {HID_KEY_CONTROL_LEFT, HID_KEY_T}, //button a
    {HID_KEY_CONTROL_LEFT, HID_KEY_T}, //button b
    {HID_KEY_CONTROL_LEFT, HID_KEY_T}, //button c
    {HID_KEY_CONTROL_LEFT, HID_KEY_T}  //button d
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
        //Create the struct
        keyboard[i].button_name = 'a' + i;
        keyboard[i].button_pin = 2 + i;
        //Initialize the buttons GPIO
        gpio_init(keyboard[i].button_pin);
        gpio_set_dir(keyboard[i].button_pin, GPIO_OUT);
        gpio_pull_down(keyboard[i].button_pin);         //When pressed button = HIGH, else button = LOW  
    }

    //Initialize switch for mode
    for(int i = 0; i < switch_size; i++)
    {
        gpio_init(switch_pins[i]);
        gpio_set_dir(switch_pins[i], GPIO_IN);
        gpio_pull_down(switch_pins[i]);
    }
}

uint32_t button_state()
{
    char state;

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

uint8_t set_keycode(uint8_t button_pressed, int i)
{
    read_mode();

    return keyboard[button_pressed - 97].keycode[i];
}

uint32_t read_mode()
{
    uint32_t mode = 0;
    uint32_t counter;

    for(int i = 0; i < switch_size; i++)
    {
        if(gpio_get(switch_pins[i]) == 1)
        {
            counter = pow(2, i);
            mode += counter;  
        }    
    }

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
}