#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BUZZER_PIN GPIO_NUM_4

void app_main(void)
{

    // Code for buzzer
    gpio_set_direction(BUZZER_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(BUZZER_PIN, 1);

    while (1)
    {
        // Beep the buzzer for 1 second
        gpio_set_level(BUZZER_PIN, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        // Turn off the buzzer for 1 second
        gpio_set_level(BUZZER_PIN, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
