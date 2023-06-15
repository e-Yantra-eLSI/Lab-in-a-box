#include <stdio.h>
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define MOTOR_ENB_PIN GPIO_NUM_4
#define MOTOR_IN3_PIN GPIO_NUM_15
#define MOTOR_IN4_PIN GPIO_NUM_2

#define MOTOR_PWM_FREQ 1000
#define MOTOR_PWM_RESOLUTION LEDC_TIMER_10_BIT
#define MOTOR_PWM_CHANNEL LEDC_CHANNEL_0

void motor_init()
{
    // Configure motor enable pin as output
    gpio_set_direction(MOTOR_ENB_PIN, GPIO_MODE_OUTPUT);

    // Configure motor input pins as output
    gpio_set_direction(MOTOR_IN3_PIN, GPIO_MODE_OUTPUT);

    gpio_set_direction(MOTOR_IN4_PIN, GPIO_MODE_OUTPUT);

    // Configure LEDC for PWM control
    ledc_timer_config_t motor_pwm_timer = {
        .duty_resolution = MOTOR_PWM_RESOLUTION,
        .freq_hz = MOTOR_PWM_FREQ,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ledc_timer_config(&motor_pwm_timer);

    ledc_channel_config_t motor_pwm_channel = {
        .channel = MOTOR_PWM_CHANNEL,
        .duty = 0,
        .gpio_num = MOTOR_ENB_PIN,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_TIMER_0};
    ledc_channel_config(&motor_pwm_channel);
}

void motor_set_direction(bool clockwise)
{
    if (clockwise)
    {
        gpio_set_level(MOTOR_IN3_PIN, 1);
        gpio_set_level(MOTOR_IN4_PIN, 0);
    }
    else
    {
        gpio_set_level(MOTOR_IN3_PIN, 0);
        gpio_set_level(MOTOR_IN4_PIN, 1);
    }
}

void motor_set_speed(uint32_t speed)
{
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, MOTOR_PWM_CHANNEL, speed);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, MOTOR_PWM_CHANNEL);
}

void app_main(void)
{
    motor_init();
    bool direction = true;

    while (1)
    {
        motor_set_direction(direction); // Set motor direction clockwise
        motor_set_speed(500);           // Set motor speed to 500 (0-1023 range)

        // Wait for some time to observe the motor behavior
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        motor_set_speed(0); // Stop the motor

        motor_set_direction(!direction); // Set motor direction counterclockwise
        motor_set_speed(800);            // Set motor speed to 800 (0-1023 range)

        // Wait for some time to observe the motor behavior
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}