#include "contact.h"

Contact::Contact(){
    username = "";
    displayName = "";
}

Contact::Contact(string username, string displayName) {
    this->username = username;
    this->displayName = displayName;
}

Contact::Contact(json j) {
    this->username = j.at("username").get<string>();
    this->displayName = j.at("displayName").get<string>();
}

string Contact::getUsername() {
    return username;
}

string Contact::getDisplayName() {
    return displayName;
}

string Contact::toString() {
    stringstream ss;
    // for some reason you cant use << on strings
    ss << username << " " << displayName;
    return ss.str();
}