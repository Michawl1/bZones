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
    bzones::interfaces::IPinEvent** _pinEvents,
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
                        m_pinEvents[8][i].PinEvent(
                            8,
                            portB & 0x01);
                    }
                    Serial.println("Pin 8");
                }
                break;

                case 0x02:
                {
                    for(i = 0; i < m_pinEventsSize[9]; i++)
                    {
                        m_pinEvents[9][i].PinEvent(
                            9,
                            portB & 0x02);
                    }
                    Serial.println("Pin 9");
                }
                break;
                
                case 0x04:
                {
                    for(i = 0; i < m_pinEventsSize[10]; i++)
                    {
                        m_pinEvents[10][i].PinEvent(
                            10,
                            portB & 0x04);
                    }
                    Serial.println("Pin 10");
                }
                break;
                
                case 0x08:
                {
                    for(i = 0; i < m_pinEventsSize[11]; i++)
                    {
                        m_pinEvents[11][i].PinEvent(
                            11,
                            portB & 0x08);
                    }
                    Serial.println("Pin 11");
                }
                break;
                
                case 0x10:
                {
                    for(i = 0; i < m_pinEventsSize[12]; i++)
                    {
                        m_pinEvents[12][i].PinEvent(
                            12,
                            portB & 0x10);
                    }
                    Serial.println("Pin 12");
                }
                break;
                
                case 0x20:
                {
                    for(i = 0; i < m_pinEventsSize[13]; i++)
                    {
                        m_pinEvents[13][i].PinEvent(
                            13,
                            portB & 0x20);
                    }
                    Serial.println("Pin 13");
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
                        m_pinEvents[0][i].PinEvent(
                            0,
                            portD & 0x01);
                    }
                    Serial.println("Pin 0");
                }
                break;

                case 0x02:
                {
                    for(i = 0; i < m_pinEventsSize[1]; i++)
                    {
                        m_pinEvents[1][i].PinEvent(
                            1,
                            portD & 0x02);
                    }
                    Serial.println("Pin 1");
                }
                break;
                
                case 0x04:
                {
                    for(i = 0; i < m_pinEventsSize[2]; i++)
                    {
                        m_pinEvents[2][i].PinEvent(
                            2,
                            portD & 0x04);
                    }
                    Serial.println("Pin 2");
                }
                break;
                
                case 0x08:
                {
                    for(i = 0; i < m_pinEventsSize[3]; i++)
                    {
                        m_pinEvents[3][i].PinEvent(
                            3,
                            portD & 0x08);
                    }
                    Serial.println("Pin 3");
                }
                break;
                
                case 0x10:
                {
                    for(i = 0; i < m_pinEventsSize[4]; i++)
                    {
                        m_pinEvents[4][i].PinEvent(
                            4,
                            portD & 0x10);
                    }
                    Serial.println("Pin 4");
                }
                break;
                
                case 0x20:
                {
                    for(i = 0; i < m_pinEventsSize[5]; i++)
                    {
                        m_pinEvents[5][i].PinEvent(
                            5,
                            portD & 0x20);
                    }
                    Serial.println("Pin 5");
                }
                break;
                
                case 0x40:
                {
                    for(i = 0; i < m_pinEventsSize[6]; i++)
                    {
                        m_pinEvents[6][i].PinEvent(
                            6,
                            portD & 0x40);
                    }
                    Serial.println("Pin 6");
                }
                break;
                
                case 0x80:
                {
                    for(i = 0; i < m_pinEventsSize[7]; i++)
                    {
                        m_pinEvents[7][i].PinEvent(
                            7,
                            portD & 0x80);
                    }
                    Serial.println("Pin 7");
                }
                break;
            }

            m_prevDState = portD;
        }
    }
}