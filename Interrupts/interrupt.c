#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
/*
********************************************************************************
ESP32 GPIO Interrupts
If button pressed, turn off LED for 500ms
********************************************************************************/

#define BUTTON_PIN GPIO_NUM_4
#define LED_PIN GPIO_NUM_2
#define ESP_INTR_FLAG_DEFAULT 0

static QueueHandle_t gpio_evt_queue = NULL;

static void IRAM_ATTR button_isr_handler(void *arg)
{

    uint32_t gpio_num = (uint32_t)arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL); // Send the ISR's gpio_num argument to the queue
}

static void button_task(void *arg)
{
    while (true)
    {
        uint32_t gpio_num;
        // printf("Waiting for button press interrupt\n");
        if (xQueueReceive(gpio_evt_queue, &gpio_num, portMAX_DELAY))
        {
            printf("Button pressed! Interrupt occurred on GPIO %ld\n", gpio_num);
            gpio_set_level(LED_PIN, 0); // Turn off the LED
        }
    }
}

void app_main()
{
    gpio_config_t io_conf;

    // Configure the button pin as input with pull-up resistor
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << BUTTON_PIN);
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);

    // Configure the LED pin as output
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << LED_PIN);
    gpio_config(&io_conf);

    // Create a queue to handle button events
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    if (gpio_evt_queue == NULL)
    {
        printf("Failed to create GPIO event queue\n");
        return;
    }

    // Configure and install the ISR (Interrupt Service Routine)
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    gpio_isr_handler_add(BUTTON_PIN, button_isr_handler, (void *)BUTTON_PIN);

    // Create a task to handle button events
    xTaskCreate(button_task, "button_task", 2048, NULL, 5, NULL); // Higher priority than the LED task

    while (true)
    {
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(LED_PIN, 1); // Turn on the LED
    }
}
