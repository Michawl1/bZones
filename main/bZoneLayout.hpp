/*
 *******************************************************************************
 * @file bZoneLayout.hpp
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 14 October 2023
 * 
 * @brief This file outlines a block zone task for the layout.
 * @details
 * 
 *******************************************************************************
 */

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "interfaces/ITask.hpp"
#include "interfaces/IBlockZone.hpp"

#pragma once

namespace bzones
{
    namespace tasks
    {
        class bZoneLayout:
            public bzones::interfaces::ITask,
            public bzones::interfaces::IBlockZone
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
                 * @brief A pointer to the next block zone used to know if this
                 * one is clear or not.
                 */
                bzones::interfaces::IBlockZone* m_nextZone;
            
            public:
                /**
                 * @brief Empty constructor.
                 * @pre
                 * @post
                 * @return This method performs an operation and does not return
                 * a value.
                 * @details
                 */
                bZoneLayout(
                    void);

                /**
                 * @brief Initializes this object.
                 * @pre
                 * @post
                 * @param[in] The next block zone, used to know if it is safe to
                 * dispatch.
                 * @return This method performs an operation and does not return
                 * a value.
                 * @details
                 */
                void init(
                    bzones::interfaces::IBlockZone* _nextZone);

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