// Derived from DevilutionX's Source/appfat.cpp
// License: https://github.com/diasurgical/devilutionX/blob/master/LICENSE.md

#pragma once

#include <cstdlib>
#include <cstdio>
#include <string>

inline void app_fatal(const std::string &msg)
{
    std::fputs(msg.c_str(), stderr);
    std::abort();
}
