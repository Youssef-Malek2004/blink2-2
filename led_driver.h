#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>

// Function declarations
void led_init(uint8_t gpio);
void set_led_on(uint8_t pin);
void set_led_off(uint8_t pin);

#endif 
