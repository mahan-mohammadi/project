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
    j.at("id").get_to(id);
    j.at("username").get_to(username);
    j.at("displayName").get_to(displayName);
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

json Contact::toJson() {
    return {
        {"id", id},
        {"username", username},
        {"displayName", displayName}
    };
}


int Contact::getID(){
    return id;
}

Contact::Contact(User user){
    id = user.getID();
    username = user.getUsername();
    displayName = user.getDName();
}