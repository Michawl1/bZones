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
static bzones::tasks::bZoneStation g_stationTask;
static TaskHandle_t g_stationTaskHandler;

/**
 * @brief A static wrapper to spin a object based task.
 * @pre
 * @post
 * @return This function performs an operation and does not return a value.
 * @details
 */
static void taskLauncher(
    bzones::interfaces::ITask* _iTask);
static void taskLauncher2(
    bzones::interfaces::ITask* _iTask);

void setup(
    void)
{
    Serial.begin(9600);
    while(!Serial);

    Serial.println("Starting...");
    g_blinkTask.init();
    xTaskCreate(
        taskLauncher,
        "Blink",
        192,
        &g_blinkTask,
        0,
        &g_blinkTaskHandler);

    g_stationTask.init(
        &g_stationTask);
    xTaskCreate(
        taskLauncher,
        "Station",
        192,
        &g_stationTask,
        1,
        &g_stationTaskHandler);
}

void loop(
    void)
{
}

void taskLauncher(
    bzones::interfaces::ITask* _iTask)
{
    _iTask->run();
}

void taskLauncher2(
    bzones::interfaces::ITask* _iTask)
{
    _iTask->run();
}