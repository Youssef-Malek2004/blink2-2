#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <stdint.h>

// Function declarations
void ultrasonic_sensor_init();
float read_distance();
float calculate_speed(float prev_distance, float curr_distance, float elapsed_time_ms);

#endif // ULTRASONIC_SENSOR_H
