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
: m_currState(bzones::tasks::stationStates::RESET),
  m_isInitialized(false),
  m_isOccupied(true),
  m_isStopSensor(false),
  m_isTrainExitSensor(false),
  m_motorDriver(nullptr),
  m_nextZone(nullptr),
  m_stopSensorPin(0),
  m_trainExitSensorPin(0)
{
}

void NS::bZoneStation::init(
    uint8_t _stopSensorPin,
    uint8_t _trainExitSensorPin,
    bzones::interfaces::IBlockZone* _nextZone,
    Adafruit_PWMServoDriver* _motorDriver)
{
    m_stopSensorPin = _stopSensorPin;
    m_trainExitSensorPin = _trainExitSensorPin;
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
    if(_pin == m_stopSensorPin
        && _state == 0)
    {
        m_isStopSensor = true;
    }
    else if(_pin == m_trainExitSensorPin
        && _state == 0)
    {
        m_isTrainExitSensor = true;
    }
}

void NS::bZoneStation::run(
    void)
{
    while(true)
    {
        switch(m_currState)
        {
            case stationStates::WAITING_FOR_STOP_SENSOR:
            {
                if(m_isStopSensor)
                {
                    m_isOccupied = true;
                    m_motorDriver->setPWM(
                        4,
                        0,
                        0);
                    m_currState = stationStates::STATION_OPERATIONS;
                }
            }
            break;

            case stationStates::STATION_OPERATIONS:
            {
                vTaskDelay(2000 / portTICK_PERIOD_MS);
                m_currState = stationStates::WAITING_FOR_NEXT_ZONE_CLEAR;
            }
            break;

            case stationStates::WAITING_FOR_NEXT_ZONE_CLEAR:
            {
                if(!m_nextZone->isOccupied())
                {
                    m_motorDriver->setPWM(
                        4,
                        0,
                        4095);
                    m_currState = stationStates::WAITING_FOR_TRAIN_EXIT;
                }
            }
            break;

            case stationStates::WAITING_FOR_TRAIN_EXIT:
            {
                if(m_isTrainExitSensor)
                {
                    m_currState = stationStates::RESET;
                }
            }
            break;

            case stationStates::RESET:
            {
                m_isStopSensor = false;
                m_isTrainExitSensor = false;
                m_isOccupied = false;

                m_motorDriver->setPWM(
                    4,
                    0,
                    4095);
                m_currState = stationStates::WAITING_FOR_STOP_SENSOR;
            }
            break;
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}