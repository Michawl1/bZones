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
: m_currState(bzones::tasks::layoutStates::INIT),
  m_enterSensorPin(0),
  m_exitSensorPin(0),
  m_holdSensorPin(0),
  m_isEnterSensor(false),
  m_isExitSensor(false),
  m_isHoldSensor(false),
  m_isInitialized(false),
  m_isOccupied(true),
  m_motorDriver(nullptr),
  m_nextZone(nullptr)
{
}

void NS::bZoneLayout::init(
    uint8_t _enterSensorPin,
    uint8_t _holdSensorPin,
    uint8_t _exitSensorPin,
    bzones::interfaces::IBlockZone* _nextZone,
    Adafruit_PWMServoDriver* _motorDriver)
{
    m_enterSensorPin = _enterSensorPin;
    m_holdSensorPin = _holdSensorPin;
    m_exitSensorPin = _exitSensorPin;
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
    if(_pin == m_enterSensorPin
        && _state == 0)
    {
        m_isEnterSensor = true;
    }
    else if(_pin == m_holdSensorPin
        && _state == 0)
    {
        m_isHoldSensor = true;
    }
    else if(_pin == m_exitSensorPin
        && _state == 0)
    {
        m_isExitSensor = true;
    }
}

void NS::bZoneLayout::run(
    void)
{
    while(true)
    {
        switch(m_currState)
        {
            case layoutStates::INIT:
            {
                m_currState = layoutStates::WAITING_FOR_NEXT_ZONE_CLEAR;
            }
            break;

            case layoutStates::WAITING_FOR_ENTER_SENSOR:
            {
                if(m_isEnterSensor)
                {
                    m_isOccupied = true;
                    m_currState = layoutStates::WAITING_FOR_HOLD_SENSOR;
                }
            }
            break;

            case layoutStates::WAITING_FOR_HOLD_SENSOR:
            {
                if(m_isHoldSensor)
                {
                    m_currState = layoutStates::WAITING_FOR_NEXT_ZONE_CLEAR;
                }
            }
            break;

            case layoutStates::WAITING_FOR_NEXT_ZONE_CLEAR:
            {
                if(!m_nextZone->isOccupied())
                {
                    m_motorDriver->setPWM(
                        2,
                        0,
                        4095);
                    m_currState = layoutStates::WAITING_FOR_EXIT_SENSOR;
                }
            }
            break;

            case layoutStates::WAITING_FOR_EXIT_SENSOR:
            {
                if(m_isExitSensor)
                {
                    vTaskDelay(1500 / portTICK_PERIOD_MS);
                    m_motorDriver->setPWM(
                        2,
                        0,
                        0);
                    m_currState = layoutStates::RESET;
                }
            }
            break;

            case layoutStates::RESET:
            {
                m_isOccupied = false;                
                m_isEnterSensor = false;
                m_isHoldSensor = false;
                m_isExitSensor = false;

                m_currState = layoutStates::WAITING_FOR_ENTER_SENSOR;
            }
            break;
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}