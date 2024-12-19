#include "led_driver.h"
#include "pico/stdlib.h"

void led_init(uint8_t gpio){
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_OUT);
}

void set_led_on(uint8_t pin){
    gpio_put(pin, true);
}

void set_led_off(uint8_t pin){
    gpio_put(pin, false);
}