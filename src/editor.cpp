// Simple CLI for extracting and updating Diablo save files without loading assets.

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <cstring>
#include <memory>

#include "codec.h"
#include "hero_json.h"
#include "pack.h"
#include "pfile.h"
#include "mpq/mpq_writer.hpp"

namespace devilution {
uint32_t gSaveNumber;
}

using namespace devilution;
using nlohmann::json;

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0]
              << " <save file> [json file] [--create] [--multi] [--spawn] [--hellfire]\n";
    return 1;
  }

  std::filesystem::path savePath{argv[1]};
  std::filesystem::path jsonPath;

  bool createMode = false;
  bool flagMulti = false;
  bool flagSpawn = false;
  bool flagHellfire = false;

  int argIndex = 2;
  if (argIndex < argc && argv[argIndex][0] != '-') {
    jsonPath = argv[argIndex++];
  }
  for (; argIndex < argc; ++argIndex) {
    std::string_view arg = argv[argIndex];
    if (arg == "--create")
      createMode = true;
    else if (arg == "--multi")
      flagMulti = true;
    else if (arg == "--spawn")
      flagSpawn = true;
    else if (arg == "--hellfire")
      flagHellfire = true;
    else {
      std::cerr << "Unknown flag: " << arg << "\n";
      return 1;
    }
  }

  if (!createMode && !std::filesystem::exists(savePath)) {
    std::cerr << "Save file does not exist: " << savePath << "\n";
    return 1;
  }

  gSaveNumber = 0;
  gbIsMultiplayer = flagMulti;
  gbIsSpawn = flagSpawn;
  gbIsHellfire = flagHellfire || savePath.extension() == ".hsv";
  gbIsHellfireSaveGame = gbIsHellfire;

  PlayerPack pack{};
  if (!createMode) {
    int32_t error;
    auto archive = MpqArchive::Open(savePath.string().c_str(), error);
    if (!archive) {
      std::cerr << "Unable to open save archive: " << MpqArchive::ErrorMessage(error) << "\n";
      return 1;
    }
    size_t size = 0;
    auto heroData = ReadArchive(*archive, "hero", &size);
    if (heroData == nullptr || size != sizeof(PlayerPack)) {
      std::cerr << "Invalid hero data\n";
      return 1;
    }
    memcpy(&pack, heroData.get(), sizeof(PlayerPack));
  }

  if (createMode) {
    if (jsonPath.empty()) {
      std::cerr << "JSON file is required for create\n";
      return 1;
    }
    std::ifstream in(jsonPath);
    if (!in) {
      std::cerr << "Unable to open JSON file: " << jsonPath << "\n";
      return 1;
    }
    json j;
    in >> j;
    JsonToPlayerPack(j, pack);

    if (!flagMulti)
      gbIsMultiplayer = pack.pBattleNet != 0;

    MpqWriter saveWriter(savePath.string().c_str());
    const size_t packedLen = codec_get_encoded_len(sizeof(pack));
    std::unique_ptr<std::byte[]> packed(new std::byte[packedLen]);
    memcpy(packed.get(), &pack, sizeof(pack));
    codec_encode(packed.get(), sizeof(pack), packedLen, pfile_get_password());
    saveWriter.WriteFile("hero", packed.get(), packedLen);
    saveWriter.RemoveHashEntry("game");
  } else {
    json j = PlayerPackToJson(pack);
    if (!jsonPath.empty()) {
      std::ofstream out(jsonPath);
      if (!out) {
        std::cerr << "Unable to open output file: " << jsonPath << "\n";
        return 1;
      }
      out << j.dump(2);
    } else {
      std::cout << j.dump(2) << "\n";
    }
  }

  return 0;
}
