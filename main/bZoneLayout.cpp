/*
 *******************************************************************************
 * @file bZoneLayout.cpp
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 13 October 2023
 * 
 * @brief This file outlines a block zone task for a layout.
 * @details
 * 
 *******************************************************************************
 */

#include <Arduino.h>
#include "bZoneLayout.hpp"

namespace NS = bzones::tasks;

NS::bZoneLayout::bZoneLayout(
    void)
: m_isInitialized(false),
  m_isOccupied(true)
{
}

void NS::bZoneLayout::init(
    bzones::interfaces::IBlockZone* _nextZone,
    Adafruit_PWMServoDriver* _motorDriver)
{
    m_nextZone = _nextZone;
    m_motorDriver = _motorDriver;

    m_isInitialized = true;
}

bool NS::bZoneLayout::isOccupied(
    void)
{
    return m_isOccupied;
}

void NS::bZoneLayout::run(
    void)
{
    TaskHandle_t currTask = xTaskGetCurrentTaskHandle();
    Serial.println("Starting task: " + String(pcTaskGetName(currTask)));

    bool toggle = true;

    while(true)
    {
        if(toggle)
        {
            toggle = !toggle;
            m_motorDriver->setPWM(
                0,
                0,
                100);
        }
        else
        {
            toggle = !toggle;
            m_motorDriver->setPWM(
                0,
                0,
                300);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}