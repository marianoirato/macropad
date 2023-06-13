#ifndef _OLED_H_
#define _OLED_H_

#include "ssd1306.h"

#define SCL_PIN 18
#define SDA_PIN 19

void setup_gpio(void);
ssd1306_t * get_display();
void setup_display(ssd1306_t *);
void display(const char *, uint32_t, uint32_t, uint32_t);
void display_mode(uint16_t);

#endif