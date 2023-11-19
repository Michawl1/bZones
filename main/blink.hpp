/*
 *******************************************************************************
 * @file Blink.hpp
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 13 October 2023
 * 
 * @brief This file defines a concrete task that blinks an led.
 * @details
 * 
 *******************************************************************************
 */

#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include "interfaces/ITask.hpp"

#pragma once

namespace bzones
{
    namespace tasks
    {
        class Blink: public bzones::interfaces::ITask
        {
            private:
                /**
                 * @brief A flag to indicate that this object has been 
                 * initialized.
                 */
                bool m_isInitialized;
            
            public:
                /**
                 * @brief Empty constructor.
                 * @pre
                 * @post
                 * @return This method performs an operation and does not return
                 * a value.
                 * @details
                 */
                Blink(
                    void);

                /**
                 * @brief Initializes this object.
                 * @pre
                 * @post
                 * @return This method performs an operation and does not return
                 * a value.
                 * @details
                 */
                void init(
                    void);

                /**
                 * @brief Runs this object's task.
                 * @pre This object has been initialized.
                 * @post
                 * @return This method performs an operation and does not return
                 * a value.
                 * @details
                 */
                void run(
                    void) override;
        };
    } // namespace tasks
} // namespace bzones