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
#include "interfaces/IPinEvent.hpp"
#include "interfaces/ITask.hpp"
#include "blink.hpp"
#include "bZoneLayout.hpp"
#include "bZoneLiftHill.hpp"
#include "bZoneStation.hpp"
#include "bZoneTransferTrack.hpp"
#include "Constants.hpp"
#include "halReaderTask.hpp"

#define configMINIMAL_STACK_SIZE    ((unsigned short)32)

namespace CONSTANTS = bzones::constants;

static bzones::tasks::Blink g_blinkTask;
static bzones::tasks::bZoneLayout g_bZoneLayout;
static bzones::tasks::bZoneLiftHill g_bZoneLiftHill;
static bzones::tasks::bZoneStation g_bZoneStation;
static bzones::tasks::bZoneTransferTrack g_bZoneTransferTrack;
static bzones::tasks::HalReaderTask g_halReaderTask;
static Adafruit_PWMServoDriver g_motorDriver;

static bzones::interfaces::IPinEvent* g_pinEventNotifiers[CONSTANTS::PIN_EVENT_NOTIFIERS_SIZE];

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

    pinMode(13, OUTPUT);

    for(uint8_t i = 0; i < 10; i++)
    {
        pinMode(i, INPUT_PULLUP);
    }

    g_motorDriver.begin();
    g_motorDriver.setOscillatorFrequency(25000000);
    g_motorDriver.setPWMFreq(50);

    Serial.println("Starting...");

    g_blinkTask.init();
    xTaskCreate(
        taskLauncher,
        nullptr,
        CONSTANTS::BLINK_TASK_STACK_SIZE,
        &g_blinkTask,
        CONSTANTS::Priority::BLINK,
        nullptr);

    g_bZoneLiftHill.init(
        2,
        3,
        4,
        &g_bZoneLayout,
        &g_motorDriver);
    xTaskCreate(
        taskLauncher,
        nullptr,
        CONSTANTS::LIFT_HILL_READER_TASK_STACK_SIZE,
        &g_bZoneLiftHill,
        CONSTANTS::Priority::ZONES,
        nullptr);
    g_pinEventNotifiers[0] = &g_bZoneLiftHill;
        
    g_bZoneLayout.init(
        &g_bZoneTransferTrack);
    xTaskCreate(
        taskLauncher,
        nullptr,
        CONSTANTS::LIFT_HILL_READER_TASK_STACK_SIZE,
        &g_bZoneLayout,
        CONSTANTS::Priority::ZONES,
        nullptr);
    g_pinEventNotifiers[1] = &g_bZoneLayout;

    g_bZoneTransferTrack.init(
        &g_bZoneStation,
        &g_motorDriver);
    xTaskCreate(
        taskLauncher,
        nullptr,
        CONSTANTS::TRANSFER_TRACK_STACK_SIZE,
        &g_bZoneTransferTrack,
        CONSTANTS::Priority::ZONES,
        nullptr);
    g_pinEventNotifiers[2] = &g_bZoneTransferTrack;
    
    g_bZoneStation.init(
        &g_bZoneLiftHill,
        &g_motorDriver);
    // xTaskCreate(
    //     taskLauncher,
    //     nullptr,
    //     CONSTANTS::STATION_TASK_STACK_SIZE,
    //     &g_bZoneStation,
    //     CONSTANTS::Priority::ZONES,
    //     nullptr);
    //g_pinEventNotifiers[3] = &g_bZoneStation;

    g_halReaderTask.init(
        0b00000011,
        0b11111111,
        g_pinEventNotifiers,
        CONSTANTS::PIN_EVENT_NOTIFIERS_SIZE);
    xTaskCreate(
        taskLauncher,
        nullptr,
        CONSTANTS::HAL_READER_TASK_STACK_SIZE,
        &g_halReaderTask,
        CONSTANTS::Priority::HAL_READER,
        nullptr);
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
