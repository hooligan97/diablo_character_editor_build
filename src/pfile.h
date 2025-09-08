// Derived from DevilutionX's Source/pfile.h
// License: https://github.com/diasurgical/devilutionX/blob/master/LICENSE.md

#pragma once
#include <cstddef>
#include <memory>
#include <string>

#include "mpq/mpq_reader.hpp"

namespace devilution {

const char *pfile_get_password();
std::unique_ptr<std::byte[]> ReadArchive(MpqArchive &archive, const char *pszName, size_t *pdwLen);

extern bool gbIsMultiplayer;
extern bool gbIsSpawn;
extern bool gbIsHellfire;
extern bool gbIsHellfireSaveGame;

} // namespace devilution
