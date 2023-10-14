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
            STATION = 1
        };

        /**
         * @brief The name of the blink task.
         */
        const char* BLINK_TASK_NAME = "Blink";

        /**
         * @brief The size of the stack for the blink task.
         */
        const uint16_t BLINK_TASK_STACK_SIZE = 192;

        /**
         * @brief The name of the station task.
         */
        const char* STATION_TASK_NAME = "Station";

        /**
         * @brief The size of the stack for the station task.
         */
        const uint16_t STATION_TASK_STACK_SIZE = 192;
    } // namespace contants
} // namespace bzones