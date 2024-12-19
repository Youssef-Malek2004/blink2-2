#include "ultrasonic_sensor.h"
#include "pico/stdlib.h"

// Define Ultrasonic Sensor Pins
const uint trig_pin = 28;
const uint echo_pin = 29;

// Initialize ultrasonic sensor
void ultrasonic_sensor_init() {
    gpio_init(trig_pin);
    gpio_set_dir(trig_pin, GPIO_OUT);
    gpio_put(trig_pin, false); // Ensure Trig is LOW

    gpio_init(echo_pin);
    gpio_set_dir(echo_pin, GPIO_IN);
}

// Function to read distance
float read_distance() {
    // Send a 10µs HIGH pulse to the Trig pin
    gpio_put(trig_pin, true);
    sleep_us(10);
    gpio_put(trig_pin, false);

    // Wait for the Echo pin to go HIGH
    while (gpio_get(echo_pin) == 0);

    // Measure the time Echo pin stays HIGH
    uint64_t start_time = time_us_64();
    while (gpio_get(echo_pin) == 1);
    uint64_t end_time = time_us_64();

    // Calculate the distance in centimeters
    float pulse_duration = (float)(end_time - start_time); // in microseconds
    float distance = (pulse_duration / 58.0f); // Convert to cm
    return distance;
}

// Function to calculate speed
float calculate_speed(float prev_distance, float curr_distance, float elapsed_time_ms) {
    float delta_distance = curr_distance - prev_distance; // Change in distance (cm)
    float speed = delta_distance / (elapsed_time_ms / 1000.0f); // Speed in cm/s
    return speed;
}
