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
  m_isNewPinEvent(false),
  m_isOccupied(true),
  m_motorDriver(nullptr),
  m_nextZone(nullptr),
  m_pinEventPin(0),
  m_pinEventState(0)
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

void NS::bZoneLayout::pinEvent(
    uint8_t _pin,
    uint8_t _state)
{
    m_isNewPinEvent = true;
    m_pinEventPin = _pin;
    m_pinEventState = _state;

    Serial.println(m_pinEventPin);
}

void NS::bZoneLayout::run(
    void)
{
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