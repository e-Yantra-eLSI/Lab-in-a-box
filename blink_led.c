
#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_4

void app_main(void)
{

    // Code for led blinking
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_4, 1);

    while (1)
    {
        // Turn on the led for 1 second
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        // Turn off the led for 1 second
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
