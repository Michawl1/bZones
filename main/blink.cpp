/*
 *******************************************************************************
 * @file Blink.hpp
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 13 October 2023
 * 
 * @brief This file implements a concrete task that blinks an led.
 * @details
 * 
 *******************************************************************************
 */

#include "blink.hpp"

namespace NS = bzones::tasks;

NS::Blink::Blink(
    void)
: m_isInitialized(false)
{

}

void NS::Blink::init(
    void)
{
    m_isInitialized = true;
}

void NS::Blink::run(
    void)
{
    pinMode(13, OUTPUT);
    while(true)
    {
        digitalWrite(13, HIGH);
        vTaskDelay(50);
        digitalWrite(13, LOW);
        vTaskDelay(50);
    }
}