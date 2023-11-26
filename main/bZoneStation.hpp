/*
 *******************************************************************************
 * @file bZoneStation.hpp
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 13 October 2023
 * 
 * @brief This file outlines a block zone task for a station.
 * @details
 * 
 *******************************************************************************
 */

#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "interfaces/IBlockZone.hpp"
#include "interfaces/IPinEvent.hpp"
#include "interfaces/ITask.hpp"

#pragma once

namespace bzones
{
    namespace tasks
    {
        class bZoneStation:
            public bzones::interfaces::ITask,
            public bzones::interfaces::IBlockZone,
            public bzones::interfaces::IPinEvent
        {
            private:
                /**
                 * @brief A flag to indicate that this object has been 
                 * initialized.
                 */
                bool m_isInitialized;

                /**
                 * @brief A flag that keeps track of if this block zone is
                 * occupied.
                 */
                bool m_isOccupied;

                /**
                 * @brief A flag to indicate that a new pin event occurred.
                 */
                bool m_isNewPinEvent;

                /**
                 * @brief The motor driver used to control all motors on the
                 * system.
                 */
                Adafruit_PWMServoDriver* m_motorDriver;

                /**
                 * @brief A pointer to the next block zone used to know if this
                 * one is clear or not.
                 */
                bzones::interfaces::IBlockZone* m_nextZone;

                /**
                 * @brief The pin number that gets called from a pin event.
                 */
                uint8_t m_pinEventPin;

                /**
                 * @brief The state of the pin from the pin event.
                 */
                uint8_t m_pinEventState;
            
            public:
                /**
                 * @brief Empty constructor.
                 * @pre
                 * @post
                 * @return This method performs an operation and does not return
                 * a value.
                 * @details
                 */
                bZoneStation(
                    void);

                /**
                 * @brief Initializes this object.
                 * @pre
                 * @post
                 * @param[in] _nextZone The next block zone, used to know if it 
                 * is safe to dispatch.
                 * @param[in] _motorDriver The motor driver used to control all
                 * motors on the system.
                 * @return This method performs an operation and does not return
                 * a value.
                 * @details
                 */
                void init(
                    bzones::interfaces::IBlockZone* _nextZone,
                    Adafruit_PWMServoDriver* _motorDriver);

                /**
                 * @brief Tells the user if this block zone is occupied.
                 * @pre
                 * @post
                 * @return True if this block zone has a train in it, false
                 * otherwise.
                 * @details
                 */
                bool isOccupied(
                    void) override;

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
                void pinEvent(
                    uint8_t _pin,
                    uint8_t _state) override;

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