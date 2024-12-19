#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h> // For uint32_t and uint8_t

// Function declarations
void motor_driver_init();
void move_forward(uint8_t speed);
void move_right(uint8_t speed);
void move_left(uint8_t speed);
void stop_motors();
void set_motor_speed(uint32_t pin, uint8_t speed);

#endif // MOTOR_DRIVER_H
