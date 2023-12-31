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
: m_currState(bzones::tasks::liftHillStates::RESET),
  m_exitLiftSensorPin(0),
  m_isExitLiftSensor(false),
  m_isInitialized(false),
  m_isOccupied(true),
  m_isLiftSensor(false),
  m_isPanicSensor(false),
  m_liftHillSensorPin(0),
  m_motorDriver(nullptr),
  m_nextZone(nullptr),
  m_panicSensorPin(0)
{
}

void NS::bZoneLiftHill::init(
    uint8_t _liftHillSensorPin,
    uint8_t _panicSensorPin,
    uint8_t _exitLiftSensorPin,
    bzones::interfaces::IBlockZone* _nextZone,
    Adafruit_PWMServoDriver* _motorDriver)
{
    m_liftHillSensorPin = _liftHillSensorPin;
    m_panicSensorPin = _panicSensorPin;
    m_exitLiftSensorPin = _exitLiftSensorPin;
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
    if(_pin == m_liftHillSensorPin
        && _state == 0)
    {
        m_isLiftSensor = true;
    }
    else if(_pin == m_panicSensorPin
        && _state == 0)
    {
        m_isPanicSensor = true;
    }
    else if(_pin == m_exitLiftSensorPin
        && _state == 0)
    {
        m_isExitLiftSensor = true;
    }
}

void NS::bZoneLiftHill::run(
    void)
{
    while(true)
    {
        switch(m_currState)
        {
            case liftHillStates::WAITING_FOR_LIFT_SENSOR:
            {
                if(m_isLiftSensor)
                {
                    m_currState = liftHillStates::WAITING_FOR_NEXT_ZONE_CLEAR;
                    m_isOccupied = true;
                }
            }
            break;

            case liftHillStates::WAITING_FOR_NEXT_ZONE_CLEAR:
            {
                if(m_nextZone->isOccupied()
                    && m_isPanicSensor)
                {
                    m_motorDriver->setPWM(
                        15,
                        0,
                        0);
                }
                else if(!m_nextZone->isOccupied())
                {                  
                    m_currState = liftHillStates::WAITING_FOR_EXIT_SENSOR;
                }
            }
            break;

            case liftHillStates::WAITING_FOR_EXIT_SENSOR:
            {
                m_motorDriver->setPWM(
                    15,
                    0,
                    4095);

                if(m_isExitLiftSensor)
                {
                    m_currState = liftHillStates::RESET;
                }
            }
            break;

            case liftHillStates::RESET:
            {
                m_currState = liftHillStates::WAITING_FOR_LIFT_SENSOR;
                
                m_motorDriver->setPWM(
                    15,
                    0,
                    1000);
                
                // Wait a bit for the train to leave.
                vTaskDelay(250 / portTICK_PERIOD_MS);
                m_isLiftSensor = false;
                m_isPanicSensor = false;
                m_isExitLiftSensor = false;
            }
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}