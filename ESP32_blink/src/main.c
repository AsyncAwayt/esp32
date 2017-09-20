#include <stdio.h>
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include "sdkconfig.h"

// Define the pin that drives the built-in LED
#define BLINK_GPIO  (gpio_num_t) 2

// Task that contains the blinking LED code
void blink_task(void *pvParameters)
{
  // Configure IOMUX register for the pin
  gpio_pad_select_gpio(BLINK_GPIO);
  // Configure the GPIO as output
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
  while(1)
  {
    // Set output to HIGH
    gpio_set_level(BLINK_GPIO, 1);
    // Wait for 500ms
    vTaskDelay(pdMS_TO_TICKS(500));
    // Set output to LOW
    gpio_set_level(BLINK_GPIO, 0);
    // Wait for 500ms
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// Compulsory main procedure
void app_main()
{
  // Create the blink task
  xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
}
