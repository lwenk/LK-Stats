#include "mod/Stats/Stats.h"

#include <filesystem>
#include <memory>
#include <utility>

#include <nlohmann/json.hpp>

#include "ll/api/io/FileUtils.h"

#include "mod/Events/Events.h"
#include "mod/Hook/Hook.h"
#include "mod/Stats/Command/RegisterCommand.h"
#include "mod/Stats/StatsType.h"


namespace stats {
namespace {
PlayerStatsMap playerStatsMap;
StatsCache     statsCache;
} // namespace

PlayerStatsMap& getPlayerStatsMap() { return playerStatsMap; }
StatsCache&     getStatsCache() { return statsCache; }

StatsCacheData parseStatsData(const std::string& data) {
    auto j             = nlohmann::json::parse(data);
    auto tmpData       = std::make_shared<StatsData>();
    auto tmpInfo       = PlayerInfo();
    tmpInfo.name       = j["playerInfo"]["name"];
    tmpInfo.uuid       = j["playerInfo"]["uuid"];
    tmpInfo.xuid       = j["playerInfo"]["xuid"];
    tmpData->custom    = j["minecraft:custom"];
    tmpData->mined     = j["minecraft:mined"];
    tmpData->broken    = j["minecraft:broken"];
    tmpData->crafted   = j["minecraft:crafted"];
    tmpData->used      = j["minecraft:used"];
    tmpData->picked_up = j["minecraft:picked_up"];
    tmpData->dropped   = j["minecraft:dropped"];
    tmpData->killed    = j["minecraft:killed"];
    tmpData->killed_by = j["minecraft:killed_by"];
    StatsCacheData r   = std::make_pair(tmpInfo, tmpData);
    return r;
}

void loadStatsCache() {
    auto        statsPath = ll::file_utils::u8path("./stats");
    std::string extension = ".json";
    for (const auto& entry : std::filesystem::directory_iterator(statsPath)) {
        // 检查文件是否为所需后缀
        if (entry.path().extension() == extension) {
            auto rawData = ll::file_utils::readFile(entry.path());
            auto data    = parseStatsData(*rawData);
            statsCache.push_back(data);
        }
    }
}

void load() {
    event::listenEvents();
    hook::hook();
    command::registerCommand();
    loadStatsCache();
}

void unload() {
    event::removeEvents();
    hook::unhook();
}
} // namespace stats