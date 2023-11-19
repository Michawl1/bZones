/*
 *******************************************************************************
 * @file bZoneLiftHill.cpp
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 19 November 2023
 * 
 * @brief This file outlines a block zone task for the layout.
 * @details
 * 
 *******************************************************************************
 */

#include <Arduino.h>
#include "bZoneLiftHill.hpp"

namespace NS = bzones::tasks;

NS::bZoneLiftHill::bZoneLiftHill(
    void)
: m_isInitialized(false),
  m_isOccupied(true)
{
}

void NS::bZoneLiftHill::init(
    bzones::interfaces::IBlockZone* _nextZone,
    Adafruit_PWMServoDriver* _motorDriver)
{
    m_nextZone = _nextZone;
    m_motorDriver = _motorDriver;

    m_isInitialized = true;
}

bool NS::bZoneLiftHill::isOccupied(
    void)
{
    return m_isOccupied;
}

void NS::bZoneLiftHill::pinEvent(
    uint8_t _pin,
    uint8_t _state)
{
    m_isNewPinEvent = true;
    m_pinEventPin = _pin;
    m_pinEventState = _state;
}

void NS::bZoneLiftHill::run(
    void)
{
    TaskHandle_t currTask = xTaskGetCurrentTaskHandle();
    Serial.println("Starting task: " + String(pcTaskGetName(currTask)));

    while(true)
    {
        if(m_isNewPinEvent)
        {
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}