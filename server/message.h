#include <ctime>
#include <string>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Message{
    public:
    //TODO: add a json constructor and a to json????? also add to and from json
    Message();
    Message(int, int, string );
    // so we can load from the db without updating the timestamp
    Message(int, int , string , time_t );
    Message(json);
    int getSenderId();
    int getReciverId();
    string getMessage();
    time_t getTime();
    json toJson();
    private:
    int senderId;
    int reciverId;
    string message;
    time_t time;
};