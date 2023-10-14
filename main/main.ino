/*
 *******************************************************************************
 * @file main.ino
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 13 October 2023
 * 
 * @brief This file outlines the main loop for the bZones project.
 * @details bZones is a block zones project for model roller coasters designed
 * to run on an Richard Barry's version of free rtos running on an arduino uno.
 * 
 *******************************************************************************
 */
#include <Arduino_FreeRTOS.h>

static TaskHandle_t g_blinkTaskHandler;
static TaskHandle_t g_serialTaskHandler;
static TaskHandle_t g_serialTaskHandler2;

/**
 * @brief Starts a blink task.
 * @pre
 * @post
 * @return This function performs an operation and does not return a value.
 * @details
 */
static void blinkTask(
    void* _params);

static void serialTask(
    void* _params);

void setup(
    void)
{
    Serial.begin(9600);
    while(!Serial);

    Serial.println("Starting...");
    xTaskCreate(
        blinkTask,
        "Blink",
        192,
        nullptr,
        0,
        &g_blinkTaskHandler);

    xTaskCreate(
        serialTask,
        "Serial",
        192,
        nullptr,
        1,
        &g_serialTaskHandler);
    
    xTaskCreate(
        serialTask,
        "Other",
        192,
        nullptr,
        2,
        &g_serialTaskHandler2);
}

void loop(
    void)
{
}

void blinkTask(
    void* _params)
{
    pinMode(13, OUTPUT);
    while(true)
    {
        digitalWrite(13, HIGH);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        digitalWrite(13, LOW);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void serialTask(
    void* _params)
{
    uint8_t i = 0;
    while(true)
    {
        TaskHandle_t currTask = xTaskGetCurrentTaskHandle();
        Serial.println(String(pcTaskGetName(currTask)) + " " + String(i));
        i++;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}