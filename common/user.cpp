#include "user.h"

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

string User::getUsername() {
    return this->username;
}

string User::getDName() {
    return this->displayName;
}

//need to add encdenc
string User::getPass() {
    return this->encPass;
}

void User::print(){
    cout << "id: " << id << " display name: " << displayName << " username: " << username << '\n';
}


