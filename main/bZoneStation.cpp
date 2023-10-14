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
  m_isOccupied(false)
{
}

void NS::bZoneStation::init(
    void)
{
    m_isInitialized = true;
}

void NS::bZoneStation::run(
    void)
{
    TaskHandle_t currTask = xTaskGetCurrentTaskHandle();
    Serial.println("Starting task: " + String(pcTaskGetName(currTask)));
    while(true)
    {
        Serial.println("station");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}