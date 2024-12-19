#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include <stdint.h>
#include <stdbool.h>

// Function declarations
void ir_sensor_init();
uint16_t read_right_ir();
uint16_t read_left_ir();

#endif 
