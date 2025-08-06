#include <ctime>
#include <string>
#include "json.hpp"

using namespace std;

class Message{
    public:
    //TODO: add a json constructor and a to json????? also add to and from json
    Message();
    Message(int senderId, int reciverId, string content);
    // so we can load from the db without updating the timestamp
    Message(int senderId, int reciverId, string content, time_t time);
    int getSenderId();
    int getReciverId();
    string getMessage();
    time_t getTime();
    private:
    int senderId;
    int reciverId;
    string content;
    time_t time;
};