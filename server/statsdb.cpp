#include "statsdb.h"
#include <iostream>
#include <fstream>

StatsDB::StatsDB() {
    filename = "stats.json";
    load();
}

void StatsDB::load() {
    ifstream file(filename);
    if (file.good()) {
        file >> stats;
    } else {
        stats["totalUsers"] = 0;
        stats["totalMessages"] = 0;
    }
}

void StatsDB::save() {
    ofstream file(filename);
    file << stats.dump(2);
}

void StatsDB::addMessageCountByOne() {
    stats["totalMessages"] = stats.at("totalMessages").get<int>() + 1;
    save();
}

void StatsDB::addUserCountByOne() {
    stats["totalUsers"] = stats.at("totalUsers").get<int>() + 1;
    save();
}

int StatsDB::getUserCount() {
    return stats.at("totalUsers").get<int>();
}

int StatsDB::getMessageCount() {
    return stats.at("totalMessages").get<int>();
}