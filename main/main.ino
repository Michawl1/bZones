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
#include "ITask.hpp"
#include "blink.hpp"

static bzones::tasks::Blink g_blinkTask;
static TaskHandle_t g_blinkTaskHandler;

/**
 * @brief A static wrapper to spin a object based task.
 * @pre
 * @post
 * @return This function performs an operation and does not return a value.
 * @details
 */
static void taskLauncher(
    void* _iTask);

void setup(
    void)
{
    g_blinkTask.init();

    xTaskCreate(
        taskLauncher,
        "Blink",
        512,
        &g_blinkTask,
        1,
        &g_blinkTaskHandler);
}

void loop(
    void)
{
}

void taskLauncher(
    void* _iTask)
{
    bzones::interfaces::ITask* instance = reinterpret_cast<bzones::interfaces::ITask*>(_iTask);
    instance->run();
}