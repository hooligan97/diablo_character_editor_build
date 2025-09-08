// Derived from DevilutionX's Source/utils/str_cat.hpp
// License: https://github.com/diasurgical/devilutionX/blob/master/LICENSE.md

#pragma once
#include <sstream>
#include <string>

namespace devilution {

template <typename... Args>
inline std::string StrCat(Args&&... args)
{
    std::ostringstream oss;
    (oss << ... << args);
    return oss.str();
}

}
