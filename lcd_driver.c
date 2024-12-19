#include "lcd_driver.h"
#include "pico/stdlib.h"

void lcd_write_command(uint8_t command) {
    uint8_t data[2] = {0x00, command};
    i2c_write_blocking(I2C_PORT, LCD_ADDRESS, data, 2, false);
}

void lcd_write_data(uint8_t data) {
    uint8_t buffer[2] = {0x40, data};
    i2c_write_blocking(I2C_PORT, LCD_ADDRESS, buffer, 2, false);
}

void lcd_init() {
    i2c_init(I2C_PORT, 100 * 1000); // 100 kHz
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    sleep_ms(100);  // Wait for power-on
    lcd_write_command(0x33);
    sleep_ms(5);
    lcd_write_command(0x32);
    sleep_ms(5);
    lcd_write_command(0x28);
    sleep_ms(5);
    lcd_write_command(0x0C);
    sleep_ms(5);
    lcd_write_command(0x06);
    sleep_ms(5);
    lcd_write_command(0x01);
    sleep_ms(5);
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

void lcd_clear() {
    lcd_write_command(0x01);
    sleep_ms(5);
}
