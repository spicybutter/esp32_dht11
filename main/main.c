#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "dht.h"

// DHT11 data pin — update this to match how the sensor is wired on your board.
#define DHT_GPIO_PIN GPIO_NUM_18

static const char *TAG = "dht11";

void app_main(void)
{
    while (1) {
        float temperature = 0;
        float humidity = 0;

        esp_err_t result = dht_read_float_data(DHT_TYPE_DHT11, DHT_GPIO_PIN, &humidity, &temperature);

        if (result == ESP_OK) {
            ESP_LOGI(TAG, "Temperature: %.1f C, Humidity: %.1f %%", temperature, humidity);
        } else {
            ESP_LOGE(TAG, "Failed to read from DHT11 sensor (error %d)", result);
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
