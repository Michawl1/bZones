/*
 *******************************************************************************
 * @file bZoneLiftHill.hpp
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 19 November 2023
 * 
 * @brief This file outlines a block zone task for the layout.
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
        namespace liftHillStates 
        {
            enum LiftHillStates : uint8_t
            {
                WAITING_FOR_LIFT_SENSOR = 1,
                WAITING_FOR_NEXT_ZONE_CLEAR = 2,
                WAITING_FOR_EXIT_SENSOR = 3,
                RESET
            };
        } // namespace liftHillStates

        class bZoneLiftHill:
            public bzones::interfaces::ITask,
            public bzones::interfaces::IBlockZone,
            public bzones::interfaces::IPinEvent
        {
            private:
                /**
                 * @brief The current state of this task.
                 */
                liftHillStates::LiftHillStates m_currState;

                /**
                 * @brief The pin index for the exit lift hill sensor.
                 */
                uint8_t m_exitLiftSensorPin;

                /**
                 * @brief A flag to indicate that the exit lift hill sensor
                 * has been activated.
                 */
                bool m_isExitLiftSensor;

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
                 * @brief A flag to indicate that the lift sensor has been 
                 * activated.
                 */
                bool m_isLiftSensor;

                /**
                 * @brief A flag to indicate that the panic sensor has been 
                 * activated.
                 */
                bool m_isPanicSensor;

                /**
                 * @brief The pin index for the lift hill sensor.
                */
                uint8_t m_liftHillSensorPin;

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
                 * @brief The pin index for the panic sensor.
                 */
                uint8_t m_panicSensorPin;
            
            public:
                /**
                 * @brief Empty constructor.
                 * @pre
                 * @post
                 * @return This method performs an operation and does not return
                 * a value.
                 * @details
                 */
                bZoneLiftHill(
                    void);

                /**
                 * @brief Initializes this object.
                 * @pre
                 * @post
                 * @param[in] _liftHillSensorPin The pin index for the lift hill
                 * sensor.
                 * @param[in] _panicSensorPin The pin index for the panic 
                 * sensor.
                 * @param[in] _exitLiftSensorPin The pin index for the exit lift
                 * hill sensor.
                 * @param[in] _nextZone The next block zone, used to know if it 
                 * is safe to dispatch.
                 * @param[in] _motorDriver The motor driver used to control all
                 * motors on the system.
                 * @return This method performs an operation and does not return
                 * a value.
                 * @details
                 */
                void init(
                    uint8_t _liftHillSensorPin,
                    uint8_t _panicSensorPin,
                    uint8_t _exitLiftSensorPin,
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