// Derived from DevilutionX's Source/utils/file_util.h
// License: https://github.com/diasurgical/devilutionX/blob/master/LICENSE.md

#pragma once
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <string_view>
#include <sys/stat.h>
#include <unistd.h>

namespace devilution {

inline bool FileExists(const char *path)
{
    struct stat st;
    return stat(path, &st) == 0;
}

inline bool GetFileSize(const char *path, std::uintmax_t *size)
{
    struct stat st;
    if (stat(path, &st) != 0)
        return false;
    if (size != nullptr)
        *size = st.st_size;
    return true;
}

inline bool ResizeFile(const char *path, std::uintmax_t size)
{
    return truncate(path, size) == 0;
}

inline std::string_view Dirname(const char *path)
{
    const char *slash = std::strrchr(path, '/');
    if (slash == nullptr)
        return {};
    return std::string_view(path, slash - path);
}

inline bool RecursivelyCreateDir(const char *path)
{
    if (path == nullptr || *path == '\0')
        return true;
    struct stat st;
    if (stat(path, &st) == 0)
        return S_ISDIR(st.st_mode);
    std::string_view parent = Dirname(path);
    if (!parent.empty()) {
        std::string parentStr(parent);
        if (!RecursivelyCreateDir(parentStr.c_str()))
            return false;
    }
    return mkdir(path, 0777) == 0;
}

} // namespace devilution
