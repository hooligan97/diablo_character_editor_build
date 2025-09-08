// Portions derived from DevilutionX. License:
// https://github.com/diasurgical/devilutionX/blob/master/LICENSE.md

#pragma once

#include <nlohmann/json.hpp>

#include "pack.h"

namespace devilution {

nlohmann::json PlayerPackToJson(const PlayerPack &pack);
void JsonToPlayerPack(const nlohmann::json &j, PlayerPack &pack);

} // namespace devilution
