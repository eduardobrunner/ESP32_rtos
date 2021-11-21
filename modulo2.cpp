#include "modulo2.h"

TaskHandle_t TaskHandle_modulo2_task;

void modulo2_task(void *parameter)
{
    data_t msg_buffer;
    Serial.println("Modulo2: Se creo la tarea!!");

    randomSeed(15);

    strcpy(msg_buffer.msg, "Val Modulo2:");

    while (1)
    {
        //Serial.println("Modulo2: enviando!");
        msg_buffer.valor = random(300);
        modulo1_send(&msg_buffer);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void modulo2_launch()
{
    xTaskCreatePinnedToCore(      // Use xTaskCreate() in vanilla FreeRTOS
        modulo2_task,             // Function to be called
        "modulo2_task",           // Name of task
        10000,                    // Stack size (bytes in ESP32, words in FreeRTOS)
        NULL,                     // Parameter to pass
        1,                        // Task priority
        &TaskHandle_modulo2_task, // Task handle
        APP_CORE);                // Run on one core for demo purposes (ESP32 only)
}

void modulo2_kill()
{
    if (TaskHandle_modulo2_task != NULL)
    {
        vTaskDelete(TaskHandle_modulo2_task);
        TaskHandle_modulo2_task = NULL;
    }
}
