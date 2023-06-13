#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "ssd1306.h"
#include "oled.h"
#include "keyboard.h"
#include "mode_name.h"

void setup_gpio(void) {
    i2c_init(i2c1, 400000);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SCL_PIN);
    gpio_pull_up(SDA_PIN);
}

ssd1306_t * get_display(){
    static ssd1306_t display;

    return &display;
}

void setup_display(ssd1306_t *display){
    display->external_vcc = false;
    
    display->initialized = ssd1306_init(display, 128, 64, 0x3C, i2c1);
    ssd1306_clear(display);
}

void display(const char * data, uint32_t x, uint32_t y, uint32_t scale){
    ssd1306_t * display = get_display();

    if(display->initialized == false)
        setup_display(display);

    ssd1306_draw_string(display, x, y, scale, data);
    ssd1306_show(display);
}

void clear_display(){
    ssd1306_clear(get_display());
}

void display_mode(uint16_t mode_selected){
    static int last_mode = -1;   

    if(mode_selected != last_mode)
    {
        clear_display();
        display(mode_name[mode_selected], 0, 0, 2);
    }

    last_mode = mode_selected; 
}