#include "modulo1.h"

TaskHandle_t TaskHandle_modulo1_task;

QueueHandle_t msg_queue_toModulo1;

void modulo1_task(void *parameter)
{
    data_t msg_buffer;
    TickType_t xPeriod;

    Serial.println("Modulo 1: Se creo la tarea!!");

    xPeriod = pdMS_TO_TICKS(1000);

    while (1)
    {
        if (xQueueReceive(msg_queue_toModulo1, (void *)&msg_buffer, xPeriod) == pdTRUE)
        {
            Serial.printf("Modulo1: %s %d\n", msg_buffer.msg, msg_buffer.valor);
            
            // Print out remaining stack memory (words)
            Serial.printf("LED: \t\t\t\t\t HWM (words): %d\n", uxTaskGetStackHighWaterMark(NULL));
        }
        else
        {
            Serial.println("Modulo1: No recibi nada wacho!");
        }
    }
}

void modulo1_launch()
{
    msg_queue_toModulo1 = xQueueCreate(5, sizeof(data_t));

    xTaskCreatePinnedToCore(      // Use xTaskCreate() in vanilla FreeRTOS
        modulo1_task,             // Function to be called
        "modulo1_task",           // Name of task
        2000,                    // Stack size (bytes in ESP32, words in FreeRTOS)
        NULL,                     // Parameter to pass
        1,                        // Task priority
        &TaskHandle_modulo1_task, // Task handle
        APP_CORE);                // Run on one core for demo purposes (ESP32 only)
}

void modulo1_kill()
{
    if (TaskHandle_modulo1_task != NULL)
    {
        vTaskDelete(TaskHandle_modulo1_task);
        TaskHandle_modulo1_task = NULL;
    }

    if (msg_queue_toModulo1 != NULL)
    {
        vQueueDelete(msg_queue_toModulo1);
        msg_queue_toModulo1 = NULL;
    }
}

void modulo1_send(data_t *msg)
{
    if (msg_queue_toModulo1 != NULL)
    {
        if (xQueueSend(msg_queue_toModulo1, (void *)msg, 0) != pdTRUE)
        {
            Serial.println("Modulo1: full queue_toModulo1");
        }
    }
}