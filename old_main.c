#include "motor_driver.h"
#include "ultrasonic_sensor.h"
#include "ir_sensor.h"
#include "led_driver.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include <stdio.h>

#define I2C_PORT i2c0
#define SDA_PIN 4
#define SCL_PIN 5
#define LCD_ADDRESS 0x27

const float threshold_distance = 25.0;
const uint led_pin = 18;
const uint led_pin_ir = 19;       // LED connected to pin 19

const uint16_t red_threshold_upper = 180; // Adjust this value based on testing
const uint16_t red_threshold_lower = 100;

void lcd_write_command(uint8_t command) {
    uint8_t data[2] = {0x00, command};
    i2c_write_blocking(I2C_PORT, LCD_ADDRESS, data, 2, false);
}

void lcd_write_data(uint8_t data) {
    uint8_t buffer[2] = {0x40, data};
    i2c_write_blocking(I2C_PORT, LCD_ADDRESS, buffer, 2, false);
}

void lcd_init() {
    sleep_ms(100);  // Wait longer for LCD to power on
    lcd_write_command(0x33); // Initialize
    sleep_ms(100);
    lcd_write_command(0x32); // Set to 4-bit mode
    sleep_ms(100);
    lcd_write_command(0x28); // 2 lines, 5x7 matrix
    sleep_ms(100);
    lcd_write_command(0x0C); // Display on, cursor off
    sleep_ms(100);
    lcd_write_command(0x06); // Move cursor right
    sleep_ms(100);
    lcd_write_command(0x01); // Clear display
    sleep_ms(100);           // Wait for the clear command to execute
}

void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t positions[] = {0x80, 0xC0};
    lcd_write_command(positions[row] + col);
}

void lcd_print(const char *str) {
    while (*str) {
        lcd_write_data(*str++);
    }
}

int main() {
    stdio_init_all();
    motor_driver_init();
    ultrasonic_sensor_init();
    led_init(led_pin);
    led_init(led_pin_ir);
    ir_sensor_init();

     // Initialize I2C
    i2c_init(I2C_PORT, 100 * 1000); // 100 kHz frequency
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    // Initialize LCD
    lcd_init();
    lcd_set_cursor(0, 0);
    lcd_print("Initializing...");
    
    float prev_distance = 0.0f;
    float curr_distance = 0.0f;
    uint64_t prev_time = time_us_64();

    sleep_ms(2000);

    while (true) {
        float distance = read_distance();
        curr_distance = distance;

        uint64_t curr_time = time_us_64();

        // Calculate elapsed time in milliseconds
        float elapsed_time_ms = (curr_time - prev_time) / 1000.0f;

        // Calculate speed
        float speed = calculate_speed(prev_distance, curr_distance, elapsed_time_ms);

        printf("Distance: %.2f cm\n", curr_distance);
        printf("Speed: %.2f m/s\n", speed/100);

        // Update previous values
        prev_distance = curr_distance;
        prev_time = curr_time;

        uint16_t right_ir_value = read_right_ir(); // Channel 0 for pin 26
        uint16_t left_ir_value = read_left_ir();  // Channel 1 for pin 27

         // Display distance on LCD
        lcd_set_cursor(0, 0);
        lcd_print("Dist: ");
        char buffer[10];
        snprintf(buffer, sizeof(buffer), "%.2f cm", distance);
        lcd_print(buffer);

        lcd_set_cursor(1, 0);
        lcd_print("R_IR: ");
        snprintf(buffer, sizeof(buffer), "%d", right_ir_value);
        lcd_print(buffer);
        lcd_print(" L_IR: ");
        snprintf(buffer, sizeof(buffer), "%d", left_ir_value);
        lcd_print(buffer);


        if (distance > threshold_distance) {
            if (!(red_threshold_lower < right_ir_value && right_ir_value < red_threshold_upper)) {
                move_left(255);
                printf("GOING LEFT!\n");
            }else if (!(red_threshold_lower < left_ir_value && left_ir_value < red_threshold_upper)) {
                move_right(255);
                printf("GOING RIGHT!\n");
            }else if(!(red_threshold_lower < right_ir_value && right_ir_value < red_threshold_upper) && !(red_threshold_lower < left_ir_value && left_ir_value < red_threshold_upper)){
                stop_motors();
                printf("STOPPING!\n");
            }else{
                printf("MOVING FORWARD!\n");
                move_forward( 120);
            }
            printf("ULTRASONIC LED ON\n");
            set_led_on(led_pin);
        } else {
            stop_motors();
            printf("OBSTACLE DETECTED!\n");
            set_led_off(led_pin);
        }

         sleep_ms(20);
     }
}