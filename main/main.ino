/*
 *******************************************************************************
 * @file main.ino
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 13 October 2023
 * 
 * @brief This file outlines the main loop for the bZones project.
 * @details bZones is a block zones project for model roller coasters designed
 * to run on an Richard Barry's version of free rtos running on an arduino uno.
 * @note Requires 'FreeRtos' by Richard Barry v 10.5.1
 *       Requires 'Adafruit PWM Servo Driver Libary' by Adafruit v 3.0.1
 *******************************************************************************
 */

#include <Arduino_FreeRTOS.h>
#include <Adafruit_PWMServoDriver.h>
#include "interfaces/ITask.hpp"
#include "blink.hpp"
#include "bZoneLayout.hpp"
#include "bZoneStation.hpp"
#include "Constants.hpp"

static bzones::tasks::Blink g_blinkTask;
static TaskHandle_t g_blinkTaskHandler;
static bzones::tasks::bZoneLayout g_bZoneLayout;
static TaskHandle_t g_bZoneLayoutTaskHandler;
static bzones::tasks::bZoneStation g_bZoneStation;
static TaskHandle_t g_bZoneStationTaskHandler;
static Adafruit_PWMServoDriver g_motorDriver;

namespace CONSTANTS = bzones::constants;

/**
 * @brief The interrupt triggered on pins 8-13.
 * @pre
 * @post
 * @return This function performs an operation and does not return a value.
 * @details
 */
void portBChangeInterrupt(
    void);
    
/**
 * @brief The interrupt triggered on pins 0-7.
 * @pre
 * @post
 * @return This function performs an operation and does not return a value.
 * @details
 */
void portDChangeInpterrupt(
    void);

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

    for(uint8_t i = 0; i < 14; i++)
    {
        pinMode(i, INPUT_PULLUP);
    }
    attachInterrupt(digitalPinToInterrupt(0), portDChangeInpterrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(8), portBChangeInpterrupt, CHANGE);

    g_motorDriver.begin();
    g_motorDriver.setOscillatorFrequency(25000000);
    g_motorDriver.setPWMFreq(50);

    Serial.println("Starting...");

    g_blinkTask.init();
    xTaskCreate(
        taskLauncher,
        CONSTANTS::BLINK_TASK_NAME,
        CONSTANTS::BLINK_TASK_STACK_SIZE,
        &g_blinkTask,
        CONSTANTS::Priority::BLINK,
        &g_blinkTaskHandler);

    g_bZoneLayout.init(
        &g_bZoneStation,
        &g_motorDriver);
    xTaskCreate(
        taskLauncher,
        CONSTANTS::LAYOUT_TASK_NAME,
        CONSTANTS::LAYOUT_TASK_STACK_SIZE,
        &g_bZoneLayout,
        CONSTANTS::Priority::LAYOUT,
        &g_bZoneLayoutTaskHandler);

    g_bZoneStation.init(
        &g_bZoneLayout,
        &g_motorDriver);
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

void portBChangeInpterrupt(
    void)
{
    uint8_t portBState = PINB;
    
    // Assuming only one sensor triggers at a time...
    switch(portBState)
    {
        case 0:
        {

        }
        break;

        // Pin 8
        case 1:
        {

        }
        break;

        // Pin 9
        case 2:
        {

        }
        break;

        // Pin 10
        case 4:
        {

        }
        break;

        // Pin 11
        case 8:
        {

        }
        break;

        // Pin 12
        case 16:
        {

        }
        break;

        // Pin 13
        case 32:
        {

        }
        break;
    }
}

void portDChangeInpterrupt(
    void)
{
    uint8_t portDState = PIND;

    // Assuming only one sensor triggers at a time...
    switch(portDState)
    {
        case 0:
        {

        }
        break;

        // Pin 0
        case 1:
        {

        }
        break;

        // Pin 1
        case 2:
        {

        }
        break;

        // Pin 2
        case 4:
        {

        }
        break;

        // Pin 3
        case 8:
        {

        }
        break;

        // Pin 4
        case 16:
        {

        }
        break;

        // Pin 5
        case 32:
        {

        }
        break;

        // Pin 6
        case 64:
        {

        }
        break;

        // Pin 7
        case 128:
        {

        }
        break;
    }
}
