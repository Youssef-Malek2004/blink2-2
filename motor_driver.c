#include "motor_driver.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Define H-Bridge control pins
const uint32_t motor1_forward = 25;
const uint32_t motor1_backward = 15;
const uint32_t motor2_forward = 16;
const uint32_t motor2_backward = 17;

// Define PWM pins for speed control
const uint32_t motor1_pwm = 12;
const uint32_t motor2_pwm = 13;

// Initialize motor driver
void motor_driver_init() {
    // Initialize GPIO pins for motor control
    gpio_init(motor1_forward);
    gpio_set_dir(motor1_forward, GPIO_OUT);
    gpio_init(motor1_backward);
    gpio_set_dir(motor1_backward, GPIO_OUT);
    gpio_init(motor2_forward);
    gpio_set_dir(motor2_forward, GPIO_OUT);
    gpio_init(motor2_backward);
    gpio_set_dir(motor2_backward, GPIO_OUT);

    // Initialize PWM pins
    gpio_set_function(motor1_pwm, GPIO_FUNC_PWM);
    gpio_set_function(motor2_pwm, GPIO_FUNC_PWM);
    uint slice_num1 = pwm_gpio_to_slice_num(motor1_pwm);
    uint slice_num2 = pwm_gpio_to_slice_num(motor2_pwm);
    pwm_set_wrap(slice_num1, 255);
    pwm_set_wrap(slice_num2, 255);
    pwm_set_enabled(slice_num1, true);
    pwm_set_enabled(slice_num2, true);
}

// Function to move forward
void move_forward(uint8_t speed) {
    gpio_put(motor1_forward, true);
    gpio_put(motor1_backward, false);
    gpio_put(motor2_forward, true);
    gpio_put(motor2_backward, false);
    set_motor_speed(motor1_pwm, speed);
    set_motor_speed(motor2_pwm, speed/2);
}

void move_right(uint8_t speed) {
    gpio_put(motor1_forward, true);
    gpio_put(motor1_backward, false);
    gpio_put(motor2_forward, false);
    gpio_put(motor2_backward, false);
    set_motor_speed(motor1_pwm, speed);
    set_motor_speed(motor2_pwm, speed);
}

void move_left(uint8_t speed) {
    gpio_put(motor1_forward, false);
    gpio_put(motor1_backward, false);
    gpio_put(motor2_forward, true);
    gpio_put(motor2_backward, false);
    set_motor_speed(motor1_pwm, speed);
    set_motor_speed(motor2_pwm, speed);
}

// Function to stop motors
void stop_motors() {
    gpio_put(motor1_forward, false);
    gpio_put(motor1_backward, false);
    gpio_put(motor2_forward, false);
    gpio_put(motor2_backward, false);
    set_motor_speed(motor1_pwm, 0);
    set_motor_speed(motor2_pwm, 0);
}

// Function to set motor speed
void set_motor_speed(uint32_t pin, uint8_t speed) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint channel = pwm_gpio_to_channel(pin);
    pwm_set_chan_level(slice_num, channel, speed);
}
