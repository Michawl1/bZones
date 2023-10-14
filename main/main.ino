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
#include "Constants.hpp"

static bzones::tasks::Blink g_blinkTask;
static TaskHandle_t g_blinkTaskHandler;
static bzones::tasks::bZoneStation g_bZoneStation;
static TaskHandle_t g_bZoneStationTaskHandler;

namespace CONSTANTS = bzones::constants;

/**
 * @brief Generically launches a task.
 * @pre
 * @post
 * @return This function performs an operation and does not return a value.
 * @details
 */
static void taskLauncher(
    void* _param);

void setup(
    void)
{
    Serial.begin(9600);
    while(!Serial);

    Serial.println("Starting...");

    g_blinkTask.init();
    xTaskCreate(
        taskLauncher,
        CONSTANTS::BLINK_TASK_NAME,
        CONSTANTS::BLINK_TASK_STACK_SIZE,
        &g_blinkTask,
        CONSTANTS::Priority::BLINK,
        &g_blinkTaskHandler);

    g_bZoneStation.init(
        nullptr);
    xTaskCreate(
        taskLauncher,
        CONSTANTS::STATION_TASK_NAME,
        CONSTANTS::STATION_TASK_STACK_SIZE,
        &g_bZoneStation,
        CONSTANTS::Priority::STATION,
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
