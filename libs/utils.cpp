/**
 * @brief This file contains the utils functions.
 *
 * @file utils.cpp
 *
 * @see utils.hpp
 *
 * created by Zarox28
 */

#pragma once

#include <iostream>
#include <cstdlib>
#if defined(unix) || defined(__APPLE__)
#include <unistd.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

#include "utils.hpp"

namespace Utils
{
  extern void Wait(unsigned int seconds)
  {
#if defined(unix) || defined(__APPLE__)
    sleep(seconds);
#else
    Sleep(seconds);
#endif
  }
}