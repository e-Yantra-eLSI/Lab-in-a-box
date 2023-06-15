#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

static esp_adc_cal_characteristics_t adc1_chars;
double moisture = 0;
double sensor_value = 0;
void app_main(void)
{
    // Configure ADC
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);
    // Configure ADC1 Channel 4
    adc1_config_width(ADC_WIDTH_BIT_DEFAULT);
    // Set attenuation of ADC1 channel 4 to 11dB (3.9V)
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);

    while (1)
    {
        // Read ADC1 Channel 4
        sensor_value = adc1_get_raw(ADC1_CHANNEL_4);
        // Convert adc_reading to moisture percentage
        moisture = 100 - (sensor_value / 4095) * 100;
        printf("Soil Moisture is: %.2f%%\n", moisture);
        printf("\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS); // wait 5 seconds
    }
}
