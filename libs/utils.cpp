/**
 * @brief This file contains the utils functions.
 *
 * @file utils.cpp
 *
 * @see utils.hpp
 *
 * created by Zarox28
 */

#include <iostream>
#include <cstdlib>
#if defined(unix) || defined(__APPLE__)
#include <unistd.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

namespace Utils
{
    extern void Wait(unsigned int seconds)
    {
        sleep(seconds);
    }
}