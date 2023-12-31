/*
 *******************************************************************************
 * @file Constants.hpp
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 14 October 2023
 * 
 * @brief This file outlines all of the Constants used for the bZones project.
 * @details
 * 
 *******************************************************************************
 */

#include <stdint.h>

#pragma once

namespace bzones
{
    namespace constants
    {
        /**
         * @brief The priorities of all tasks, higher number = more important.
         */
        enum Priority : uint8_t
        {
            BLINK = 0,
            ZONES = 1,
            HAL_READER = 2
        };

        /**
         * @brief The size of the stack for the blink task.
         */
        const uint16_t BLINK_TASK_STACK_SIZE = 48;

        /**
         * @brief The stack size for the hal reader task.
         */
        const uint16_t HAL_READER_TASK_STACK_SIZE = 96;

        /**
         * @brief The size of the stack for the layout task.
         */
        const uint16_t LAYOUT_TASK_STACK_SIZE = 72;

        /**
         * @brief The stack size for the lift hill task.
         */
        const uint16_t LIFT_HILL_READER_TASK_STACK_SIZE = 72;

        /**
         * @brief The number of objects that subscribe to pin events.
        */
        const uint8_t PIN_EVENT_NOTIFIERS_SIZE = 4;

        /**
         * @brief The size of the stack for the station task.
         */
        const uint16_t STATION_TASK_STACK_SIZE = 72;

        /**
         * @brief The size of the stack for the transfer track task.
         */
        const uint16_t TRANSFER_TRACK_STACK_SIZE = 72;

    } // namespace contants
} // namespace bzones