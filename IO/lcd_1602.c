#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/dac.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_timer.h"
#include "esp_log.h"

#define LCD_PIN_RS GPIO_NUM_4
#define LCD_PIN_EN GPIO_NUM_5
#define LCD_PIN_D4 GPIO_NUM_18
#define LCD_PIN_D5 GPIO_NUM_19
#define LCD_PIN_D6 GPIO_NUM_21
#define LCD_PIN_D7 GPIO_NUM_22

#define LCD_CMD 0
#define LCD_DATA 1

#define LCD_NUM_ROWS 2
#define LCD_NUM_COLS 16

#define LCD_DELAY_MS 2

void lcd_send_nibble(uint8_t data)
{
    gpio_set_level(LCD_PIN_D4, (data >> 0) & 1);
    gpio_set_level(LCD_PIN_D5, (data >> 1) & 1);
    gpio_set_level(LCD_PIN_D6, (data >> 2) & 1);
    gpio_set_level(LCD_PIN_D7, (data >> 3) & 1);
}

void lcd_send_byte(uint8_t mode, uint8_t data)
{
    gpio_set_level(LCD_PIN_RS, mode);

    lcd_send_nibble(data >> 4);
    gpio_set_level(LCD_PIN_EN, 1);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    gpio_set_level(LCD_PIN_EN, 0);

    lcd_send_nibble(data);
    gpio_set_level(LCD_PIN_EN, 1);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    gpio_set_level(LCD_PIN_EN, 0);

    vTaskDelay(pdMS_TO_TICKS(LCD_DELAY_MS));
}

void lcd_send_command(uint8_t command)
{
    lcd_send_byte(LCD_CMD, command);
}

void lcd_send_data(uint8_t data)
{
    lcd_send_byte(LCD_DATA, data);
}

void lcd_init()
{
    gpio_set_direction(LCD_PIN_RS, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_PIN_EN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_PIN_D4, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_PIN_D5, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_PIN_D6, GPIO_MODE_OUTPUT);
    gpio_set_direction(LCD_PIN_D7, GPIO_MODE_OUTPUT);

    // Wait for the LCD to power up
    vTaskDelay(pdMS_TO_TICKS(50));

    // Initialization sequence
    lcd_send_nibble(0x03);
    gpio_set_level(LCD_PIN_EN, 1);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    gpio_set_level(LCD_PIN_EN, 0);

    vTaskDelay(pdMS_TO_TICKS(5));

    lcd_send_nibble(0x03);
    gpio_set_level(LCD_PIN_EN, 1);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    gpio_set_level(LCD_PIN_EN, 0);

    vTaskDelay(pdMS_TO_TICKS(1));

    lcd_send_nibble(0x03);
    gpio_set_level(LCD_PIN_EN, 1);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    gpio_set_level(LCD_PIN_EN, 0);

    vTaskDelay(pdMS_TO_TICKS(1));

    lcd_send_nibble(0x02);
    gpio_set_level(LCD_PIN_EN, 1);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    gpio_set_level(LCD_PIN_EN, 0);

    vTaskDelay(pdMS_TO_TICKS(1));

    // Function set: 2 lines, 5x8 dots
    lcd_send_command(0x28);
    // Display on, cursor off, blink off
    lcd_send_command(0x0C);
    // Entry mode set: increment mode, no shift
    lcd_send_command(0x06);

    // Clear the display
    lcd_send_command(0x01);
    vTaskDelay(pdMS_TO_TICKS(2));
}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t command = 0x80;
    if (row == 1)
        command |= 0x40;
    command += col;
    lcd_send_command(command);
    printf("Set cursor to row %d, col %d\n", row, col);
}

void lcd_print(const char *str)
{
    while (*str)
    {
        lcd_send_data(*str++);
    }
}

void app_main()
{
    lcd_init();
    lcd_set_cursor(0, 0);
    lcd_print("Welcome to Lab");
    lcd_set_cursor(1, 0);
    lcd_print("in a box! :D");
}