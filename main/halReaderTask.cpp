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
  m_prevDState(0)
{

}

void NS::HalReaderTask::init(
    uint8_t _portBInputMask,
    uint8_t _portDInputMask)
{
    m_portBInputMask = _portBInputMask;
    m_portDInputMask = _portDInputMask;

    m_isInitialized = true;
}

void NS::HalReaderTask::run(
    void)
{
    TaskHandle_t currTask = xTaskGetCurrentTaskHandle();
    Serial.println("Starting task: " + String(pcTaskGetName(currTask)));

    uint8_t portB = 0;
    uint8_t portD = 0;

    while(true)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);

        portB = PINB & m_portBInputMask;
        portD = PIND & m_portDInputMask;

        if(portB != m_prevBState)
        {
            switch(portB ^ m_prevBState)
            {
                case 1:
                {
                    Serial.println("Pin 8");
                }
                break;

                case 2:
                {
                    Serial.println("Pin 9");
                }
                break;
                
                case 4:
                {
                    Serial.println("Pin 10");
                }
                break;
                
                case 8:
                {
                    Serial.println("Pin 11");
                }
                break;
                
                case 16:
                {
                    Serial.println("Pin 12");
                }
                break;
                
                case 32:
                {
                    Serial.println("Pin 13");
                }
                break;
                
                case 64:
                {

                }
                break;
                
                case 128:
                {

                }
                break;
            }

            m_prevBState = portB;
        }

        if(portD != m_prevDState)
        {            
            switch(portD ^ m_prevDState)
            {
                case 1:
                {
                    Serial.println("Pin 0");
                }
                break;

                case 2:
                {
                    Serial.println("Pin 1");
                }
                break;
                
                case 4:
                {
                    Serial.println("Pin 2");
                }
                break;
                
                case 8:
                {
                    Serial.println("Pin 3");
                }
                break;
                
                case 16:
                {
                    Serial.println("Pin 4");
                }
                break;
                
                case 32:
                {
                    Serial.println("Pin 5");
                }
                break;
                
                case 64:
                {
                    Serial.println("Pin 6");
                }
                break;
                
                case 128:
                {
                    Serial.println("Pin 7");
                }
                break;
            }

            m_prevDState = portD;
        }
    }
}