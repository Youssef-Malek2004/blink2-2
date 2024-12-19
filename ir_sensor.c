#include "ir_sensor.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"

const uint ir_sensor_pin_right = 26; // IR sensor connected to ADC pin 12
const uint ir_sensor_pin_left = 27; // IR sensor connected to ADC pin 12

void ir_sensor_init(){
    adc_init();

    // Initialize right IR sensor
    adc_gpio_init(ir_sensor_pin_right); // Set pin 26 as ADC input
    adc_gpio_init(ir_sensor_pin_left);  // Set pin 27 as ADC input
}

uint16_t read_right_ir() {
    adc_select_input(0); // Select the corresponding ADC channel
    return adc_read();         // Read the analog value (12-bit: 0–4095)
}

uint16_t read_left_ir() {
    adc_select_input(1); // Select the corresponding ADC channel
    return adc_read();         // Read the analog value (12-bit: 0–4095)
}