#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

void app_main(void)
{
    // Intialise GPIO2 as input for button
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_INPUT);
    gpio_set_pull_mode(GPIO_NUM_2, GPIO_PULLUP_ONLY);

    // Intialise GPIO4 as output for LED
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT);

    while (true)
    {
        // If button is pressed, turn on LED
        if (gpio_get_level(GPIO_NUM_2))
        {
            gpio_set_level(GPIO_NUM_4, 1);
            printf("Button Pressed\n");
        }
        else
        {
            gpio_set_level(GPIO_NUM_4, 0);
        }

        vTaskDelay(10);
    }
}