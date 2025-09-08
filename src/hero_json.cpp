// Portions derived from DevilutionX. License:
// https://github.com/diasurgical/devilutionX/blob/master/LICENSE.md

#include "hero_json.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <string>
#include <vector>

namespace devilution {

using nlohmann::json;

namespace {

json ItemPackToJson(const ItemPack &item)
{
    return json{
        {"iSeed", item.iSeed},
        {"iCreateInfo", item.iCreateInfo},
        {"idx", item.idx},
        {"bId", item.bId},
        {"bDur", item.bDur},
        {"bMDur", item.bMDur},
        {"bCh", item.bCh},
        {"bMCh", item.bMCh},
        {"wValue", item.wValue},
        {"dwBuff", item.dwBuff},
    };
}

void JsonToItemPack(const json &j, ItemPack &item)
{
    j.at("iSeed").get_to(item.iSeed);
    j.at("iCreateInfo").get_to(item.iCreateInfo);
    j.at("idx").get_to(item.idx);
    j.at("bId").get_to(item.bId);
    j.at("bDur").get_to(item.bDur);
    j.at("bMDur").get_to(item.bMDur);
    j.at("bCh").get_to(item.bCh);
    j.at("bMCh").get_to(item.bMCh);
    j.at("wValue").get_to(item.wValue);
    j.at("dwBuff").get_to(item.dwBuff);
}

} // namespace

json PlayerPackToJson(const PlayerPack &p)
{
    json j;
    j["dwLowDateTime"] = p.dwLowDateTime;
    j["dwHighDateTime"] = p.dwHighDateTime;
    j["destAction"] = p.destAction;
    j["destParam1"] = p.destParam1;
    j["destParam2"] = p.destParam2;
    j["plrlevel"] = p.plrlevel;
    j["px"] = p.px;
    j["py"] = p.py;
    j["targx"] = p.targx;
    j["targy"] = p.targy;
    j["pName"] = std::string(p.pName, strnlen(p.pName, PlayerNameLength));
    j["pClass"] = p.pClass;
    j["pBaseStr"] = p.pBaseStr;
    j["pBaseMag"] = p.pBaseMag;
    j["pBaseDex"] = p.pBaseDex;
    j["pBaseVit"] = p.pBaseVit;
    j["pLevel"] = p.pLevel;
    j["pStatPts"] = p.pStatPts;
    j["pExperience"] = p.pExperience;
    j["pGold"] = p.pGold;
    j["pHPBase"] = p.pHPBase;
    j["pMaxHPBase"] = p.pMaxHPBase;
    j["pManaBase"] = p.pManaBase;
    j["pMaxManaBase"] = p.pMaxManaBase;
    j["pSplLvl"] = std::vector<uint8_t>(std::begin(p.pSplLvl), std::end(p.pSplLvl));
    j["pMemSpells"] = p.pMemSpells;

    json invBody = json::array();
    for (int i = 0; i < NUM_INVLOC; ++i)
        invBody.push_back(ItemPackToJson(p.InvBody[i]));
    j["InvBody"] = invBody;

    json invList = json::array();
    for (int i = 0; i < InventoryGridCells; ++i)
        invList.push_back(ItemPackToJson(p.InvList[i]));
    j["InvList"] = invList;

    j["InvGrid"] = std::vector<int8_t>(std::begin(p.InvGrid), std::end(p.InvGrid));
    j["_pNumInv"] = p._pNumInv;

    json spdList = json::array();
    for (int i = 0; i < MaxBeltItems; ++i)
        spdList.push_back(ItemPackToJson(p.SpdList[i]));
    j["SpdList"] = spdList;

    j["pTownWarps"] = p.pTownWarps;
    j["pDungMsgs"] = p.pDungMsgs;
    j["pLvlLoad"] = p.pLvlLoad;
    j["pBattleNet"] = p.pBattleNet;
    j["pManaShield"] = p.pManaShield;
    j["pDungMsgs2"] = p.pDungMsgs2;
    j["bIsHellfire"] = p.bIsHellfire;
    j["reserved"] = p.reserved;
    j["wReflections"] = p.wReflections;
    j["reserved2"] = std::vector<uint8_t>(std::begin(p.reserved2), std::end(p.reserved2));
    j["pSplLvl2"] = std::vector<uint8_t>(std::begin(p.pSplLvl2), std::end(p.pSplLvl2));
    j["wReserved8"] = p.wReserved8;
    j["pDiabloKillLevel"] = p.pDiabloKillLevel;
    j["pDifficulty"] = p.pDifficulty;
    j["pDamAcFlags"] = p.pDamAcFlags;
    j["reserved3"] = std::vector<uint8_t>(std::begin(p.reserved3), std::end(p.reserved3));
    return j;
}

void JsonToPlayerPack(const json &j, PlayerPack &p)
{
    j.at("dwLowDateTime").get_to(p.dwLowDateTime);
    j.at("dwHighDateTime").get_to(p.dwHighDateTime);
    p.destAction = static_cast<int8_t>(j.at("destAction").get<int>());
    p.destParam1 = static_cast<int8_t>(j.at("destParam1").get<int>());
    p.destParam2 = static_cast<int8_t>(j.at("destParam2").get<int>());
    j.at("plrlevel").get_to(p.plrlevel);
    j.at("px").get_to(p.px);
    j.at("py").get_to(p.py);
    j.at("targx").get_to(p.targx);
    j.at("targy").get_to(p.targy);
    std::string name = j.at("pName").get<std::string>();
    std::memset(p.pName, 0, sizeof(p.pName));
    std::strncpy(p.pName, name.c_str(), PlayerNameLength - 1);
    j.at("pClass").get_to(p.pClass);
    j.at("pBaseStr").get_to(p.pBaseStr);
    j.at("pBaseMag").get_to(p.pBaseMag);
    j.at("pBaseDex").get_to(p.pBaseDex);
    j.at("pBaseVit").get_to(p.pBaseVit);
    j.at("pLevel").get_to(p.pLevel);
    j.at("pStatPts").get_to(p.pStatPts);
    j.at("pExperience").get_to(p.pExperience);
    j.at("pGold").get_to(p.pGold);
    j.at("pHPBase").get_to(p.pHPBase);
    j.at("pMaxHPBase").get_to(p.pMaxHPBase);
    j.at("pManaBase").get_to(p.pManaBase);
    j.at("pMaxManaBase").get_to(p.pMaxManaBase);

    auto spl = j.at("pSplLvl").get<std::vector<int>>();
    for (size_t i = 0; i < spl.size() && i < std::size(p.pSplLvl); ++i)
        p.pSplLvl[i] = static_cast<uint8_t>(spl[i]);
    j.at("pMemSpells").get_to(p.pMemSpells);

    auto invBody = j.at("InvBody");
    for (size_t i = 0; i < NUM_INVLOC && i < invBody.size(); ++i)
        JsonToItemPack(invBody.at(i), p.InvBody[i]);

    auto invList = j.at("InvList");
    for (size_t i = 0; i < InventoryGridCells && i < invList.size(); ++i)
        JsonToItemPack(invList.at(i), p.InvList[i]);

    auto invGrid = j.at("InvGrid").get<std::vector<int>>();
    for (size_t i = 0; i < invGrid.size() && i < std::size(p.InvGrid); ++i)
        p.InvGrid[i] = static_cast<int8_t>(invGrid[i]);
    j.at("_pNumInv").get_to(p._pNumInv);

    auto spdList = j.at("SpdList");
    for (size_t i = 0; i < MaxBeltItems && i < spdList.size(); ++i)
        JsonToItemPack(spdList.at(i), p.SpdList[i]);

    p.pTownWarps = static_cast<int8_t>(j.at("pTownWarps").get<int>());
    p.pDungMsgs = static_cast<int8_t>(j.at("pDungMsgs").get<int>());
    p.pLvlLoad = static_cast<int8_t>(j.at("pLvlLoad").get<int>());
    j.at("pBattleNet").get_to(p.pBattleNet);
    j.at("pManaShield").get_to(p.pManaShield);
    j.at("pDungMsgs2").get_to(p.pDungMsgs2);
    p.bIsHellfire = static_cast<int8_t>(j.at("bIsHellfire").get<int>());
    j.at("reserved").get_to(p.reserved);
    j.at("wReflections").get_to(p.wReflections);

    auto reserved2 = j.at("reserved2").get<std::vector<int>>();
    for (size_t i = 0; i < reserved2.size() && i < std::size(p.reserved2); ++i)
        p.reserved2[i] = static_cast<uint8_t>(reserved2[i]);
    auto spl2 = j.at("pSplLvl2").get<std::vector<int>>();
    for (size_t i = 0; i < spl2.size() && i < std::size(p.pSplLvl2); ++i)
        p.pSplLvl2[i] = static_cast<uint8_t>(spl2[i]);
    j.at("wReserved8").get_to(p.wReserved8);
    j.at("pDiabloKillLevel").get_to(p.pDiabloKillLevel);
    j.at("pDifficulty").get_to(p.pDifficulty);
    j.at("pDamAcFlags").get_to(p.pDamAcFlags);
    auto reserved3 = j.at("reserved3").get<std::vector<int>>();
    for (size_t i = 0; i < reserved3.size() && i < std::size(p.reserved3); ++i)
        p.reserved3[i] = static_cast<uint8_t>(reserved3[i]);
}

} // namespace devilution
