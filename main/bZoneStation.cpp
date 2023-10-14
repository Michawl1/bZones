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

#include "bZoneStation.hpp"

namespace NS = bzones::tasks;

NS::bZoneStation::bZoneStation(
    void)
: m_isInitialized(false),
  m_isOccupied(false),
  m_nextBlockZone(nullptr)
{
}

void NS::bZoneStation::init(
    bzones::interfaces::IBlockZone* _nextBlockZone)
{
    m_nextBlockZone = _nextBlockZone;

    m_isInitialized = true;
}

bool NS::bZoneStation::isOccupied(
    void)
{
    return m_isOccupied;
}

void NS::bZoneStation::run(
    void)
{
    while(true)
    {
        Serial.println("station");
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}