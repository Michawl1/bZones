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
#include "interfaces/ITask.hpp"
#include "blink.hpp"
#include "bZoneStation.hpp"

static bzones::tasks::Blink g_blinkTask;
static TaskHandle_t g_blinkTaskHandler;
static bzones::tasks::bZoneStation g_bZoneStation;
static TaskHandle_t g_bZoneStationTaskHandler;

static void taskLauncher(
    void* _param);

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

    g_blinkTask.init();

    Serial.println("Starting...");
    xTaskCreate(
        taskLauncher,
        "Blink",
        192,
        &g_blinkTask,
        0,
        &g_blinkTaskHandler);

    g_bZoneStation.init();
    xTaskCreate(
        taskLauncher,
        "Station",
        192,
        &g_bZoneStation,
        1,
        &g_bZoneStationTaskHandler);
}

void loop(
    void)
{
}

void taskLauncher(
    void* _param)
{
    bzones::interfaces::ITask* instance = reinterpret_cast<bzones::interfaces::ITask*>(_param);
    instance->run();
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