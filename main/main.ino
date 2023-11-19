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
#include "Constants.hpp"
#include "halReaderTask.hpp"

#define configMINIMAL_STACK_SIZE    ((unsigned short)32)

static bzones::tasks::Blink g_blinkTask;
static TaskHandle_t g_blinkTaskHandler;
static bzones::tasks::bZoneLayout g_bZoneLayout;
static TaskHandle_t g_bZoneLayoutTaskHandler;
static bzones::tasks::bZoneLiftHill g_bZoneLiftHill;
static TaskHandle_t g_bZoneLiftHillTaskHandler;
static bzones::tasks::bZoneStation g_bZoneStation;
static TaskHandle_t g_bZoneStationTaskHandler;
static bzones::tasks::HalReaderTask g_halReaderTask;
static TaskHandle_t g_halReaderTaskHandler;
static Adafruit_PWMServoDriver g_motorDriver;
static uint8_t g_pinEventsSize[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};

static bzones::interfaces::IPinEvent* g_pin0Events[0];
static bzones::interfaces::IPinEvent* g_pin1Events[0];
static bzones::interfaces::IPinEvent* g_pin2Events[0];
static bzones::interfaces::IPinEvent* g_pin3Events[0];
static bzones::interfaces::IPinEvent* g_pin4Events[0];
static bzones::interfaces::IPinEvent* g_pin5Events[0];
static bzones::interfaces::IPinEvent* g_pin6Events[0];
static bzones::interfaces::IPinEvent* g_pin7Events[0];
static bzones::interfaces::IPinEvent* g_pin8Events[0];
static bzones::interfaces::IPinEvent* g_pin9Events[0];
static bzones::interfaces::IPinEvent* g_pin10Events[0];
static bzones::interfaces::IPinEvent* g_pin11Events[0];
static bzones::interfaces::IPinEvent* g_pin12Events[0];
static bzones::interfaces::IPinEvent* g_pin13Events[0];
static bzones::interfaces::IPinEvent** g_pinEvents[] = {
    g_pin0Events,
    g_pin1Events,
    g_pin2Events,
    g_pin3Events,
    g_pin4Events,
    g_pin5Events,
    g_pin6Events,
    g_pin7Events,
    g_pin8Events,
    g_pin9Events,
    g_pin10Events,
    g_pin11Events,
    g_pin12Events,
    g_pin13Events};

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

    pinMode(13, OUTPUT);

    for(uint8_t i = 0; i < 13; i++)
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

    g_bZoneLiftHill.init(
        &g_bZoneLayout,
        &g_motorDriver);
    xTaskCreate(
        taskLauncher,
        CONSTANTS::LIFT_HILL_READER_TASK_NAME,
        CONSTANTS::LIFT_HILL_READER_TASK_STACK_SIZE,
        &g_bZoneLiftHill,
        CONSTANTS::Priority::LAYOUT,
        &g_bZoneLiftHillTaskHandler);
    
    g_bZoneStation.init(
        &g_bZoneLiftHill,
        &g_motorDriver);
    xTaskCreate(
        taskLauncher,
        CONSTANTS::STATION_TASK_NAME,
        CONSTANTS::STATION_TASK_STACK_SIZE,
        &g_bZoneStation,
        CONSTANTS::Priority::STATION,
        &g_bZoneStationTaskHandler);

    g_halReaderTask.init(
        0b00000011,
        0b11111111,
        g_pinEvents,
        g_pinEventsSize);
    xTaskCreate(
        taskLauncher,
        CONSTANTS::HAL_READER_TASK_NAME,
        CONSTANTS::HAL_READER_TASK_STACK_SIZE,
        &g_halReaderTask,
        CONSTANTS::Priority::HAL_READER,
        &g_halReaderTaskHandler);
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
