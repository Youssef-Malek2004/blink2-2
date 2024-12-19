#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include "hardware/i2c.h"

#define I2C_PORT i2c0
#define SDA_PIN 4
#define SCL_PIN 5
#define LCD_ADDRESS 0x27

void lcd_init();
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(const char *str);
void lcd_clear();

#endif // LCD_DRIVER_H
