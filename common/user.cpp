#include "user.h"

// refotmat this
User::User() : id(-1), username(""), displayName(""), encPass("") {
    
}

User::User(int id, std::string username, std::string displayname, std::string encPass) {
    this->id = id;
    this->username = username;
    this->displayName = displayname;
    this->encPass = encPass;
}


void User::setID(int id) {
    this->id = id;
}

void User::setUsername(std::string username) {
    this->username = username;
}

void User::setDisplayname(std::string displayname) {
    this->displayName = displayname;
}

//need to add
void User::setPassword(std::string encPass) {
    this->encPass = encPass;
}

int User::getID() {
    return this->id;
}

std::string User::getUsername() {
    return this->username;
}

std::string User::getDName() {
    return this->displayName;
}

//need to add encdenc
std::string User::getPass() {
    return this->encPass;
}
