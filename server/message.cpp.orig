#include "message.h"

Message::Message(){
    senderId = 0;
    reciverId = 0;
    message = "";
    timestamp = time(nullptr);
    senderDname = "";
    reciverDname = "";
}

Message::Message(int senderId , int reciverId , string message , string senderDisplayName , string reciverDisplayName){
    this->senderId = senderId;
    this->reciverId = reciverId;
    this->message = message;
    this->senderDname = senderDisplayName;
    this->reciverDname = reciverDisplayName;
    timestamp = time(nullptr);
}

Message::Message(json j){
    this->senderId = j.at("senderId");
    this->reciverId = j.at("reciverId");
    this->message = j.at("message");
    timestamp = j.at("timestamp");
}

int Message::getSenderId() {
    return this->senderId;
}

int Message::getReciverId() {
    return this->reciverId;
}

string Message::getMessage() {
    return this->message;
}

time_t Message::getTime() {
    return this->timestamp;
}

json Message::toJson(){
    json j;
    j["senderId"] = this->senderId;
    j["reciverId"] = this->reciverId;
    j["message"] = this->message;
    j["timestamp"] = this->timestamp;
    j["senderDisplayName"] = senderDname;
    j["reciverDisplayName"] = reciverDname; 
    return j;
}

string Message::getSenderDisplayName() {
    return senderDname;
}

string Message::getReciverDisplayName() {
    return reciverDname;
}