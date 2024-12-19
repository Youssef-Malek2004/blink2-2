# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.13)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set project name and C/C++ standards
project(RobotController C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize Pico SDK
pico_sdk_init()

# --- FreeRTOS Integration ---

# Manually specify FreeRTOS kernel and port source files
add_library(FreeRTOS STATIC
    ${PICO_SDK_PATH}/lib/FreeRTOS/croutine.c
    ${PICO_SDK_PATH}/lib/FreeRTOS/event_groups.c
    ${PICO_SDK_PATH}/lib/FreeRTOS/list.c
    ${PICO_SDK_PATH}/lib/FreeRTOS/queue.c
    ${PICO_SDK_PATH}/lib/FreeRTOS/stream_buffer.c
    ${PICO_SDK_PATH}/lib/FreeRTOS/tasks.c
    ${PICO_SDK_PATH}/lib/FreeRTOS/timers.c
    ${PICO_SDK_PATH}/lib/FreeRTOS/portable/GCC/ARM_CM0/port.c
    ${PICO_SDK_PATH}/lib/FreeRTOS/portable/GCC/ARM_CM0/portASM.c
    ${PICO_SDK_PATH}/lib/FreeRTOS/portable/MemMang/heap_2.c
)

# Add FreeRTOS include directories
target_include_directories(FreeRTOS PUBLIC
    ${PICO_SDK_PATH}/lib/FreeRTOS/include
    ${PICO_SDK_PATH}/lib/FreeRTOS/portable/GCC/ARM_CM0
    ${PICO_SDK_PATH}/lib/FreeRTOS/portable/MemMang
    ${PICO_SDK_PATH}/src/common/pico_base_headers/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_gpio/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_timer/include
    ${CMAKE_SOURCE_DIR}/FreeRTOSConfig  # Path to FreeRTOSConfig.h
)

# --- Project Source Files ---

# Add source files for the project
add_executable(${PROJECT_NAME}
    main.c
    motor_driver.c
    ultrasonic_sensor.c
    ir_sensor.c
    led_driver.c
)

# --- Link Libraries ---

# Link project with required libraries
target_link_libraries(${PROJECT_NAME}
    pico_stdlib             # Standard Pico libraries (GPIO, stdio, etc.)
    hardware_pwm            # PWM support
    hardware_adc            # ADC support
    hardware_gpio           # GPIO support
    hardware_uart           # UART support
    hardware_i2c            # I2C support
    FreeRTOS                # Link FreeRTOS library
)

# --- Enable stdio over USB and Disable UART ---

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# --- Additional Output Formats ---

# Add extra output formats for UF2, bin, and hex
pico_add_extra_outputs(${PROJECT_NAME})
