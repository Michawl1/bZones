/*
 *******************************************************************************
 * @file IPinEvent.hpp
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 19 November 2023
 * 
 * @brief This file outlines an interface for someone to call when a pin event
 * occurs.
 * @details
 * 
 *******************************************************************************
 */

#include <stdint.h>

#pragma once

namespace bzones
{
    namespace interfaces
    {
        class IPinEvent
        {
            protected:
                /**
                 * @brief Virtual destructor for the interface.
                 */
                ~IPinEvent(
                    void) = default;
            
            public:
                /**
                 * @brief Tells the user if that a pin event occurred.
                 * @pre
                 * @post
                 * @param[in] _pin The number of the pin that the event occurred
                 * for.
                 * @param[in] _state The state of the pin 0 is low, 1 is high.
                 * @return True if this block zone has a train in it, false
                 * otherwise.
                 * @details
                 */
                virtual void pinEvent(
                    uint8_t _pin,
                    uint8_t _state) = 0;
        };
    } // namespace interfaces
} // namespace bzones
