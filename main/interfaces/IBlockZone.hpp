/*
 *******************************************************************************
 * @file IBlockZone.hpp
 * @author Michael Thompson (mthompsonkp11@gmail.com)
 * @date 13 October 2023
 * 
 * @brief This file outlines an interface for a block zone.
 * @details
 * 
 *******************************************************************************
 */

#pragma once

namespace bzones
{
    namespace interfaces
    {
        class IBlockZone
        {
            protected:
                /**
                 * @brief Virtual destructor for the interface.
                 */
                ~IBlockZone(
                    void) = default;
            
            public:
                /**
                 * @brief Tells the user if this block zone is occupied.
                 * @pre
                 * @post
                 * @return True if this block zone has a train in it, false
                 * otherwise.
                 * @details
                 */
                virtual bool isOccupied(
                    void) = 0;
        };
    } // namespace interfaces
} // namespace bzones
