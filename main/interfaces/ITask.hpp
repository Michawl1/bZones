/*
 *******************************************************************************
 * @file ITask.hpp
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 13 October 2023
 * 
 * @brief This file outlines an interface for tasks for Free RTOS.
 * @details
 * 
 *******************************************************************************
 */

#pragma once

namespace bzones
{
    namespace interfaces
    {
        class ITask
        {
            protected:
                /**
                 * @brief Virtual destructor for the interface.
                 */
                ~ITask(
                    void) = default;
            
            public:
                /**
                 * @brief Runs this object's task.
                 * @pre
                 * @post
                 * @return This method performs an operation and does not return
                 * a value.
                 * @details
                 */
                virtual void run(
                    void) = 0;
        };
    } // namespace interfaces
} // namespace bzones