// Derived from DevilutionX's Source/utils/logged_fstream.hpp
// License: https://github.com/diasurgical/devilutionX/blob/master/LICENSE.md

#pragma once
#include <cstdio>

namespace devilution {

struct LoggedFStream {
    bool Open(const char *path, const char *mode)
    {
        s_ = std::fopen(path, mode);
        return s_ != nullptr;
    }
    void Close()
    {
        if (s_ != nullptr) {
            std::fclose(s_);
            s_ = nullptr;
        }
    }
    bool IsOpen() const { return s_ != nullptr; }
    bool Seekp(long pos, int dir = SEEK_SET) { return std::fseek(s_, pos, dir) == 0; }
    bool Write(const void *buf, size_t size) { return std::fwrite(buf, 1, size, s_) == size; }
    bool Read(void *buf, size_t size) { return std::fread(buf, 1, size, s_) == size; }
    long Tellp() { return std::ftell(s_); }
private:
    std::FILE *s_ = nullptr;
};

} // namespace devilution
