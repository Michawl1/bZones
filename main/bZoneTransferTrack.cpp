/*
 *******************************************************************************
 * @file bZoneTransferTrack.cpp
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 30 December 2023
 * 
 * @brief This file outlines a block zone task for the transfer track.
 * @details
 * 
 *******************************************************************************
 */

 #include <Arduino.h>
 #include "bZoneTransferTrack.hpp"

 namespace NS = bzones::tasks;

 NS::bZoneTransferTrack::bZoneTransferTrack(
    void)
: m_isInitialized(false),
  m_isOccupied(true),
  m_motorDriver(nullptr),
  m_nextZone(nullptr)
{

}

void NS::bZoneTransferTrack::init(
    bzones::interfaces::IBlockZone* _nextZone,
    Adafruit_PWMServoDriver* _motorDriver)
{
    m_nextZone = _nextZone;
    m_motorDriver = _motorDriver;

    m_isInitialized = true;
}

bool NS::bZoneTransferTrack::isOccupied(
    void)
{
    return m_isOccupied;
}

void NS::bZoneTransferTrack::pinEvent(
    uint8_t _pin,
    uint8_t _state)
{
    
}

void NS::bZoneTransferTrack::run(
    void)
{
    while(true)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}