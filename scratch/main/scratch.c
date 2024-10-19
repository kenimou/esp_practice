#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"

static const char *TAG = "Main";

void app_main(void)
{
    // GPIO22 as button input
    gpio_set_direction(GPIO_NUM_22, GPIO_MODE_INPUT);
    gpio_set_pull_mode(GPIO_NUM_22, GPIO_PULLUP_ONLY);

    // GPIO2 as LED output
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    while (true)
    {
        if (gpio_get_level(GPIO_NUM_22))
        {
            // voltage high, no current? 
            gpio_set_level(GPIO_NUM_2, 0);
        }
        else
        {
            ESP_LOGI(TAG, "button pressed");
            gpio_set_level(GPIO_NUM_2, 1);
        }

        // Delay 10 MCU ticks, so that it doesn't block background tasks.
        vTaskDelay(10);
    }
}
