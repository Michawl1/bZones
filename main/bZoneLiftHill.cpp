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
: m_currState(bzones::tasks::liftHillStates::INIT),
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

void NS::bZoneLiftHill::init(
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
    
    m_motorDriver->setPWM(
        15,
        0,
        1000);
        m_currState = liftHillStates::RESET;

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

void NS::bZoneLiftHill::run(
    void)
{
    while(true)
    {
        switch(m_currState)
        {
            case liftHillStates::INIT:
            {
                m_currState = liftHillStates::RESET;
            }
            break;

            case liftHillStates::WAITING_FOR_ENTER_SENSOR:
            {
                if(m_isEnterSensor)
                {                    
                    m_motorDriver->setPWM(
                        15,
                        0,
                        2500);
                        
                    m_currState = liftHillStates::WAITING_FOR_NEXT_ZONE_CLEAR;
                    m_isOccupied = true;
                    m_isHoldSensor = false;
                    m_isExitSensor = false;
                }
            }
            break;

            case liftHillStates::WAITING_FOR_NEXT_ZONE_CLEAR:
            {
                if(m_isHoldSensor
                    && m_nextZone->isOccupied())
                {
                    m_motorDriver->setPWM(
                        15,
                        0,
                        0);
                }
                else if(!m_nextZone->isOccupied())
                {
                    m_motorDriver->setPWM(
                        15,
                        0,
                        4095);
                    m_isExitSensor = false;
                    m_currState = liftHillStates::WAITING_FOR_EXIT_SENSOR;
                }
            }
            break;

            case liftHillStates::WAITING_FOR_EXIT_SENSOR:
            {
                if(m_isExitSensor)
                {
                    vTaskDelay(250 / portTICK_PERIOD_MS);
                    m_motorDriver->setPWM(
                        15,
                        0,
                        1000);
                    m_currState = liftHillStates::RESET;
                }
            }
            break;
                        
            case liftHillStates::RESET:
            {
                m_isOccupied = false;                
                m_isEnterSensor = false;
                m_isHoldSensor = false;
                m_isExitSensor = false;

                m_currState = liftHillStates::WAITING_FOR_ENTER_SENSOR;
            }
            break;
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}