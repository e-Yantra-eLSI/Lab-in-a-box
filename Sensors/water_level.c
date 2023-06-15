#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#define POWER_PIN GPIO_NUM_4
#define SENSOR_PIN ADC1_CHANNEL_4 // GPIO32

static esp_adc_cal_characteristics_t adc1_chars;

int water_level = 0;
void app_main(void)
{

    // power pin
    gpio_set_direction(POWER_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(POWER_PIN, 0);
    // Configure ADC1
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 0, &adc1_chars);
    // Configure ADC resolution to 12 bits
    adc1_config_width(ADC_WIDTH_BIT_12);
    // Set attenuation of ADC1 channel 4 to 11dB (3.9V)
    adc1_config_channel_atten(SENSOR_PIN, ADC_ATTEN_DB_11); // ADC1_CHANNEL_4 = GPIO32

    while (1)
    {
        // Read ADC1 Channel 4
        gpio_set_level(POWER_PIN, 1);
        water_level = adc1_get_raw(SENSOR_PIN);
        gpio_set_level(POWER_PIN, 0);
        printf("Water Level is: %d\n", water_level);
        printf("\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS); // wait 5 seconds
    }
}
