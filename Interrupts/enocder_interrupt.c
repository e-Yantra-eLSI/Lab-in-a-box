#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

/*
********************************************************************************
ESP32 GPIO Interrupts
If encoder wheel rotates, the count will increase by 1 per slot on disc.
********************************************************************************/

#define ENCODER_PIN GPIO_NUM_4
#define ESP_INTR_FLAG_DEFAULT 0

static QueueHandle_t gpio_evt_queue = NULL;
long long int count = 0;
static void IRAM_ATTR button_isr_handler(void *arg)
{

    uint32_t gpio_num = (uint32_t)arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL); // Send the ISR's gpio_num argument to the queue
}

static void encoder_task(void *arg)
{
    //
    while (true)
    {
        // Wait for a GPIO event
        uint32_t gpio_num;
        if (xQueueReceive(gpio_evt_queue, &gpio_num, portMAX_DELAY)) // Wait indefinitely for the next encoder change event
        {
            count++; // Increment the counter
            printf("Count: %lld\n", count);
        }
    }
}

void app_main()
{
    gpio_config_t io_conf;

    // Configure the enocder pin as input with pull-up resistor
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << ENCODER_PIN);
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
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
    gpio_isr_handler_add(ENCODER_PIN, button_isr_handler, (void *)ENCODER_PIN); // Pass the encoder pin number as an argument

    // Create a task to handle encode events
    xTaskCreate(encoder_task, "encoder_task", 2048, NULL, 5, NULL); // Higher priority than the LED task

    while (true)
    {
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
