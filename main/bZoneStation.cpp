/*
 *******************************************************************************
 * @file bZoneStation.cpp
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 13 October 2023
 * 
 * @brief This file outlines a block zone task for a station.
 * @details
 * 
 *******************************************************************************
 */

#include <Arduino.h>
#include "bZoneStation.hpp"

namespace NS = bzones::tasks;

NS::bZoneStation::bZoneStation(
    void)
: m_isInitialized(false),
  m_isOccupied(true),
  m_isNewPinEvent(false),
  m_motorDriver(nullptr),
  m_nextZone(nullptr),
  m_pinEventPin(0),
  m_pinEventState(0)
{
}

void NS::bZoneStation::init(
    bzones::interfaces::IBlockZone* _nextZone,
    Adafruit_PWMServoDriver* _motorDriver)
{
    m_nextZone = _nextZone;
    m_motorDriver = _motorDriver;

    m_isInitialized = true;
}

bool NS::bZoneStation::isOccupied(
    void)
{
    return m_isOccupied;
}

void NS::bZoneStation::pinEvent(
    uint8_t _pin,
    uint8_t _state)
{
    m_isNewPinEvent = true;
    m_pinEventPin = _pin;
    m_pinEventState = _state;

    Serial.println(m_pinEventPin);
}

void NS::bZoneStation::run(
    void)
{
    bool toggle = true;

    while(true)
    {
        // if(toggle)
        // {
        //     toggle = !toggle;
        //     m_motorDriver->setPWM(
        //         15,
        //         0,
        //         0);
        // }
        // else
        // {
        //     toggle = !toggle;
        //     m_motorDriver->setPWM(
        //         15,
        //         0,
        //         4000);
        // }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}