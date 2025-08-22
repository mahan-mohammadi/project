#include <string>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class StatsDB {
public:
    StatsDB();
    void load();
    void save();
    void addUserCountByOne();
    void addMessageCountByOne();
    int getUserCount();
    int getMessageCount();
private:
    string filename;
    json stats;
};