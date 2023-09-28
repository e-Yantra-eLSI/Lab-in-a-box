#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/ledc.h>

// Define the GPIO pin connected to the DC FAN
#define FAN_PIN GPIO_NUM_4

// PWM configuration
#define PWM_CHANNEL LEDC_CHANNEL_0       // Use channel 0
#define PWM_TIMER LEDC_TIMER_0           // Use timer 0
#define PWM_FREQ_HZ 1000                 // Frequency of PWM signal 1kHz
#define PWM_RESOLUTION LEDC_TIMER_10_BIT // 10-bit resolution

void app_main()
{
    // Configure the FAN pin as output
    gpio_set_direction(FAN_PIN, GPIO_MODE_OUTPUT);

    // Create a task to control the PWM

    // Configure PWM settings
    ledc_timer_config_t pwmTimerConfig = {
        .duty_resolution = PWM_RESOLUTION,
        .freq_hz = PWM_FREQ_HZ,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = PWM_TIMER};
    ledc_timer_config(&pwmTimerConfig);

    // Configure PWM channel
    ledc_channel_config_t pwmChannelConfig = {
        .channel = PWM_CHANNEL,
        .duty = 0,
        .gpio_num = FAN_PIN,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .hpoint = 0,
        .timer_sel = PWM_TIMER};
    ledc_channel_config(&pwmChannelConfig);

    // Start the PWM
    ledc_fade_func_install(0);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL, 0);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL);

    // Control the PWM duty cycle
    while (1)
    {
        // Increase the duty cycle from 0% to 100%
        for (int duty = 0; duty <= (1 << PWM_RESOLUTION) - 1; duty++)
        {
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL, duty);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL);
            vTaskDelay(pdMS_TO_TICKS(10));
        }

        // Decrease the duty cycle from 100% to 0%
        for (int duty = (1 << PWM_RESOLUTION) - 1; duty >= 0; duty--)
        {
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL, duty);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL);
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
}
