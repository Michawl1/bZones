/*
 *******************************************************************************
 * @file HalReaderTask.hpp
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 18 November 2023
 * 
 * @brief This file defines a concrete task that reads all of the gpio pins 
 * where hal effect sensors are connected to.
 * @details
 * 
 *******************************************************************************
 */

#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include "interfaces/ITask.hpp"
#include "interfaces/IPinEvent.hpp"

#pragma once

namespace bzones
{
    namespace tasks
    {
        class HalReaderTask: public bzones::interfaces::ITask
        {
            private:
                /**
                 * @brief A flag to indicate that this object has been 
                 * initialized.
                 */
                bool m_isInitialized;

                /**
                 * @brief The pins to monitor on port B for changes.
                 */
                uint8_t m_portBInputMask;

                /**
                 * @brief The pins to monitor on port D for changes.
                 */
                uint8_t m_portDInputMask;

                /**
                 * @brief The previous state of the port B input staus
                 * register.
                 */
                uint8_t m_prevBState;

                /**
                 * @brief The previous state of the port D input status 
                 * register.
                 */
                uint8_t m_prevDState;

                /**
                 * @brief An array of all of the objects that subscribe to pin
                 * events.
                 */
                bzones::interfaces::IPinEvent** m_pinEvents;

                /**
                 * @brief The size of @m_pinEvents.
                 */
                uint8_t m_pinEventsSize;
            
            public:
                /**
                 * @brief Empty constructor.
                 * @pre
                 * @post
                 * @return This method performs an operation and does not return
                 * a value.
                 * @details
                 */
                HalReaderTask(
                    void);

                /**
                 * @brief Initializes this object.
                 * @pre
                 * @post
                 * @param[in] _portBInputMask The pins to monitor on port B for 
                 * changes.
                 * @param[in] _portDInputMask The pins to monitor on port D for 
                 * changes.
                 * @param[in] _pinEvents An array of all of the objects that 
                 * subscribe to pin events.
                 * @param[in] _pinEventsSize The size of @_pinEvents.
                 * @return This method performs an operation and does not return
                 * a value.
                 * @details
                 */
                void init(
                    uint8_t _portBInputMask,
                    uint8_t _portDInputMask,
                    bzones::interfaces::IPinEvent** _pinEvents,
                    uint8_t _pinEventsSize);

                /**
                 * @brief Runs this object's task.
                 * @pre
                 * @post
                 * @return This method performs an operation and does not return
                 * a value.
                 * @details
                 */
                void run(
                    void) override;

            private:
                /**
                 * @brief Helper method to get the position of a 1 in a byte.
                 * @pre
                 * @post
                 * @param[in] _byte The byte to evaluate where the 1 is.
                 * @details returns only the first found 1.
                 */
                uint8_t getBytePos(
                    uint8_t _byte);
        };
    } // namespace tasks
} // namespace bzones