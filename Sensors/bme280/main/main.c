#include <stdio.h>
#include "helper.c" // Import the helper file
#include "bme280.h"

// SensorData is a struct defined in helper.c
// It contains the temperature, pressure, and humidity
// of the BME280 sensor

void app_main(void)
{
    // Initialize I2C parameters
    i2c_master_init();

    while (1)
    {
        SensorData sensorData = readSensorData(); // read sensor data
        printf("Temperature: %.2f degC\n", sensorData.temperature);
        printf("Pressure: %.2f hPa\n", sensorData.pressure);
        printf("Humidity: %.2f %%\n", sensorData.humidity);
        vTaskDelay(2000 / portTICK_PERIOD_MS); // wait for 2 seconds
    }
}
