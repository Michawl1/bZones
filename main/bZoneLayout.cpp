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
    bzones::interfaces::IBlockZone* _nextZone)
{
    m_nextZone = _nextZone;

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
    while(true)
    {        
        if(m_isOccupied)
        {
            Serial.println("Train in: "+ String(pcTaskGetName(currTask)));
        }

        if(m_isOccupied && !m_nextZone->isOccupied())
        {
            Serial.println("Next zone is open");
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}