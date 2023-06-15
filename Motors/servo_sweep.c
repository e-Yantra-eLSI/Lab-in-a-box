#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/ledc.h>

// Define the GPIO pin connected to the servo motor
#define SERVO_PIN GPIO_NUM_4

// PWM configuration
#define PWM_CHANNEL LEDC_CHANNEL_0       // Use channel 0
#define PWM_TIMER LEDC_TIMER_0           // Use timer 0
#define PWM_FREQ_HZ 50                   // Frequency of PWM signal 50Hz
#define PWM_RESOLUTION LEDC_TIMER_12_BIT // 12-bit resolution

// Servo configuration
#define SERVO_MIN_ANGLE 0   // Minimum angle for the servo (in degrees)
#define SERVO_MAX_ANGLE 180 // Maximum angle for the servo (in degrees)
#define SERVO_MIN_DUTY 50   // Minimum duty cycle for the servo (in microseconds)
#define SERVO_MAX_DUTY 2450 // Maximum duty cycle for the servo (in microseconds)

void servoTask(void *pvParameters)
{
    while (1)

    {
        for (int angle = SERVO_MIN_ANGLE; angle <= SERVO_MAX_ANGLE; angle++)
        {
            // Calculate duty cycle based on the angle
            int duty = (SERVO_MAX_DUTY - SERVO_MIN_DUTY) * angle / (SERVO_MAX_ANGLE - SERVO_MIN_ANGLE) + SERVO_MIN_DUTY;

            // Set the duty cycle for the servo
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL, duty);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        for (int angle = SERVO_MAX_ANGLE; angle >= SERVO_MIN_ANGLE; angle--)
        {
            // Calculate duty cycle based on the angle
            int duty = (SERVO_MAX_DUTY - SERVO_MIN_DUTY) * angle / (SERVO_MAX_ANGLE - SERVO_MIN_ANGLE) + SERVO_MIN_DUTY;

            // Set the duty cycle for the servo
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL, duty);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    // Configure the servo pin as output
    gpio_set_direction(SERVO_PIN, GPIO_MODE_OUTPUT);

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
        .gpio_num = SERVO_PIN,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .hpoint = 0,
        .timer_sel = PWM_TIMER};
    ledc_channel_config(&pwmChannelConfig);

    // Start the PWM
    ledc_fade_func_install(0);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL, 0);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL);

    // Create a task to control the servo
    xTaskCreate(servoTask, "servo_task", 2048, NULL, 5, NULL);
}
