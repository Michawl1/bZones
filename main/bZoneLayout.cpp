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
  m_isOccupied(false),
  m_nextZone(nullptr)
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

void NS::bZoneLayout::pinEvent(
    uint8_t _pin,
    uint8_t _state)
{
}

void NS::bZoneLayout::run(
    void)
{
    while(true)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}