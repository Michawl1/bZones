/*
 *******************************************************************************
 * @file HalReaderTask.cpp
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 18 November 2023
 * 
 * @brief This file defines a concrete task that reads all of the gpio pins 
 * where hal effect sensors are connected to.
 * @details
 * 
 *******************************************************************************
 */


#include <Arduino.h>
#include "halReaderTask.hpp"

namespace NS = bzones::tasks;

NS::HalReaderTask::HalReaderTask(
    void)
: m_isInitialized(false),
  m_portBInputMask(0),
  m_portDInputMask(0),
  m_prevBState(0),
  m_prevDState(0),
  m_pinEvents(nullptr),
  m_pinEventsSize(0)
{

}

void NS::HalReaderTask::init(
    uint8_t _portBInputMask,
    uint8_t _portDInputMask,
    bzones::interfaces::IPinEvent** _pinEvents,
    uint8_t _pinEventsSize)
{
    m_portBInputMask = _portBInputMask;
    m_portDInputMask = _portDInputMask;
    m_pinEvents = _pinEvents;
    m_pinEventsSize = _pinEventsSize;

    m_isInitialized = true;
}

uint8_t NS::HalReaderTask::getBytePos(
    uint8_t _byte)
{
    uint8_t retVal = 0;

    if(_byte == 0)
    {
        return retVal;
    }

    while(_byte != 0)
    {
        _byte >>= 1;
        retVal ++;
    }

    return retVal;
}

void NS::HalReaderTask::run(
    void)
{
    uint8_t portB = 0;
    uint8_t portD = 0;

    while(true)
    {
        vTaskDelay(25 / portTICK_PERIOD_MS);

        portB = PINB & m_portBInputMask;
        portD = PIND & m_portDInputMask;

        if(portB != m_prevBState)
        {
            uint8_t bytePos = getBytePos(portB ^ m_prevBState);

            m_prevBState = portB;

            for(uint8_t i = 0; i < m_pinEventsSize; i++)
            {
                m_pinEvents[i]->pinEvent(
                    bytePos + 7,
                    (portB >> (bytePos - 1)) & 0x01);
            }
        }
        else if(portD != m_prevDState)
        {
            uint8_t bytePos = getBytePos(portD ^ m_prevDState);

            m_prevDState = portD;

            for(uint8_t i = 0; i < m_pinEventsSize; i++)
            {
                m_pinEvents[i]->pinEvent(
                    bytePos - 1,
                    (portD >> (bytePos - 1)) & 0x01);
            }
        }
    }
}