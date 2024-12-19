#include "motor_driver.h"
#include "ultrasonic_sensor.h"
#include "ir_sensor.h"
#include "led_driver.h"
#include "lcd_driver.h"
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

const float threshold_distance = 25.0;
const uint led_pin = 18;

const uint16_t red_threshold_upper = 180;
const uint16_t red_threshold_lower = 100;

// Shared Variables
float curr_distance = 0.0f;
uint16_t right_ir_value = 0;
uint16_t left_ir_value = 0;

// Mutex for shared resources
SemaphoreHandle_t xMutex;

// Function Prototypes
void TaskSensorRead(void *pvParameters);
void TaskMotorControl(void *pvParameters);
void TaskLCDUpdate(void *pvParameters);

// Task: Read Sensors
void TaskSensorRead(void *pvParameters) {
    while (true) {
        // Acquire Mutex for shared variables
        if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
            curr_distance = read_distance();
            right_ir_value = read_right_ir();
            left_ir_value = read_left_ir();
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(50)); // Delay 50 ms
    }
}

// Task: Motor Control
void TaskMotorControl(void *pvParameters) {
    while (true) {
        if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
            if (curr_distance > threshold_distance) {
                if (!(red_threshold_lower < right_ir_value && right_ir_value < red_threshold_upper)) {
                    move_left(255);
                    printf("GOING LEFT!\n");
                } else if (!(red_threshold_lower < left_ir_value && left_ir_value < red_threshold_upper)) {
                    move_right(255);
                    printf("GOING RIGHT!\n");
                } else {
                    move_forward(120);
                    printf("MOVING FORWARD!\n");
                }
                set_led_on(led_pin);
            } else {
                stop_motors();
                printf("OBSTACLE DETECTED!\n");
                set_led_off(led_pin);
            }
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(50)); // Delay 50 ms
    }
}

// Task: Update LCD
void TaskLCDUpdate(void *pvParameters) {
    char buffer[16];
    while (true) {
        if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
            lcd_clear();
            lcd_set_cursor(0, 0);
            snprintf(buffer, sizeof(buffer), "Dist: %.2f cm", curr_distance);
            lcd_print(buffer);

            lcd_set_cursor(1, 0);
            snprintf(buffer, sizeof(buffer), "R:%d L:%d", right_ir_value, left_ir_value);
            lcd_print(buffer);
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay 500 ms
    }
}

int main() {
    // Initialize peripherals
    stdio_init_all();
    motor_driver_init();
    ultrasonic_sensor_init();
    led_init(led_pin);
    ir_sensor_init();
    lcd_init();

    // Display initial message
    lcd_set_cursor(0, 0);
    lcd_print("Initializing...");

    // Create Mutex
    xMutex = xSemaphoreCreateMutex();
    if (xMutex == NULL) {
        printf("Mutex creation failed!\n");
        while (1);
    }

    // Create FreeRTOS tasks
    xTaskCreate(TaskSensorRead, "SensorRead", 256, NULL, 1, NULL);
    xTaskCreate(TaskMotorControl, "MotorControl", 256, NULL, 1, NULL);
    xTaskCreate(TaskLCDUpdate, "LCDUpdate", 256, NULL, 1, NULL);

    // Start Scheduler
    vTaskStartScheduler();

    // Should never reach here
    while (true);
}
