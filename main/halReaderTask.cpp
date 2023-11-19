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
  m_pinEventsSize{nullptr}
{

}

void NS::HalReaderTask::init(
    uint8_t _portBInputMask,
    uint8_t _portDInputMask,
    bzones::interfaces::IPinEvent*** _pinEvents,
    uint8_t* _pinEventsSize)
{
    m_portBInputMask = _portBInputMask;
    m_portDInputMask = _portDInputMask;
    m_pinEvents = _pinEvents;
    m_pinEventsSize = _pinEventsSize;

    m_isInitialized = true;
}

void NS::HalReaderTask::run(
    void)
{
    TaskHandle_t currTask = xTaskGetCurrentTaskHandle();
    Serial.println("Starting task: " + String(pcTaskGetName(currTask)));

    uint8_t portB = 0;
    uint8_t portD = 0;
    uint8_t i = 0;

    while(true)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);

        portB = PINB & m_portBInputMask;
        portD = PIND & m_portDInputMask;

        if(portB != m_prevBState)
        {
            switch(portB ^ m_prevBState)
            {
                case 0x01:
                {
                    for(i = 0; i < m_pinEventsSize[8]; i++)
                    {
                        m_pinEvents[8][i]->pinEvent(
                            8,
                            portB & 0x01);
                    }
                }
                break;

                case 0x02:
                {
                    for(i = 0; i < m_pinEventsSize[9]; i++)
                    {
                        m_pinEvents[9][i]->pinEvent(
                            9,
                            portB & 0x02);
                    }
                }
                break;
                
                case 0x04:
                {
                    for(i = 0; i < m_pinEventsSize[10]; i++)
                    {
                        m_pinEvents[10][i]->pinEvent(
                            10,
                            portB & 0x04);
                    }
                }
                break;
                
                case 0x08:
                {
                    for(i = 0; i < m_pinEventsSize[11]; i++)
                    {
                        m_pinEvents[11][i]->pinEvent(
                            11,
                            portB & 0x08);
                    }
                }
                break;
                
                case 0x10:
                {
                    for(i = 0; i < m_pinEventsSize[12]; i++)
                    {
                        m_pinEvents[12][i]->pinEvent(
                            12,
                            portB & 0x10);
                    }
                }
                break;
                
                case 0x20:
                {
                    for(i = 0; i < m_pinEventsSize[13]; i++)
                    {
                        m_pinEvents[13][i]->pinEvent(
                            13,
                            portB & 0x20);
                    }
                }
                break;
            }

            m_prevBState = portB;
        }

        if(portD != m_prevDState)
        {            
            switch(portD ^ m_prevDState)
            {
                case 0x01:
                {
                    for(i = 0; i < m_pinEventsSize[0]; i++)
                    {
                        m_pinEvents[0][i]->pinEvent(
                            0,
                            portD & 0x01);
                    }
                }
                break;

                case 0x02:
                {
                    for(i = 0; i < m_pinEventsSize[1]; i++)
                    {
                        m_pinEvents[1][i]->pinEvent(
                            1,
                            portD & 0x02);
                    }
                }
                break;
                
                case 0x04:
                {
                    for(i = 0; i < m_pinEventsSize[2]; i++)
                    {
                        m_pinEvents[2][i]->pinEvent(
                            2,
                            portD & 0x04);
                    }
                }
                break;
                
                case 0x08:
                {
                    for(i = 0; i < m_pinEventsSize[3]; i++)
                    {
                        m_pinEvents[3][i]->pinEvent(
                            3,
                            portD & 0x08);
                    }
                }
                break;
                
                case 0x10:
                {
                    for(i = 0; i < m_pinEventsSize[4]; i++)
                    {
                        m_pinEvents[4][i]->pinEvent(
                            4,
                            portD & 0x10);
                    }
                }
                break;
                
                case 0x20:
                {
                    for(i = 0; i < m_pinEventsSize[5]; i++)
                    {
                        m_pinEvents[5][i]->pinEvent(
                            5,
                            portD & 0x20);
                    }
                }
                break;
                
                case 0x40:
                {
                    for(i = 0; i < m_pinEventsSize[6]; i++)
                    {
                        m_pinEvents[6][i]->pinEvent(
                            6,
                            portD & 0x40);
                    }
                }
                break;
                
                case 0x80:
                {
                    for(i = 0; i < m_pinEventsSize[7]; i++)
                    {
                        m_pinEvents[7][i]->pinEvent(
                            7,
                            portD & 0x80);
                    }
                }
                break;
            }

            m_prevDState = portD;
        }
    }
}