#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define IR_PIN GPIO_NUM_2
#define BUZZER_PIN GPIO_NUM_4

void app_main(void)
{
    // Intialise GPIO2 as input for IR sensor
    gpio_set_direction(IR_PIN, GPIO_MODE_INPUT);
    // Intialise GPIO4 as output for buzzer
    gpio_set_direction(BUZZER_PIN, GPIO_MODE_OUTPUT);

    while (1)
    {
        // If object is detected, turn on buzzer
        if (!gpio_get_level(IR_PIN))
        {
            gpio_set_level(BUZZER_PIN, 0);
            printf("Object detected\n");
        }
        else
        {
            gpio_set_level(BUZZER_PIN, 1);
        }
        vTaskDelay(10); // 10ms delay
    }
}
