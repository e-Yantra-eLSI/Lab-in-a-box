#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LDR_PIN GPIO_NUM_2
#define LED_PIN GPIO_NUM_4

void app_main(void)
{
    // Intialise GPIO2 as input for IR sensor
    gpio_set_direction(LDR_PIN, GPIO_MODE_INPUT);
    // Intialise GPIO4 as output for buzzer
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while (1)
    {
        // If object is detected, turn on buzzer
        if (!gpio_get_level(LDR_PIN))
        {
            gpio_set_level(LED_PIN, 0);
            printf("Light detected, switching off the led.\n");
        }
        else
        {
            gpio_set_level(LED_PIN, 1);
        }
        vTaskDelay(10); // 10ms delay
    }
}
