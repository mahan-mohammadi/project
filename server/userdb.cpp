#include "userdb.h"
#include <fstream>
#include <sstream>

UserDB::UserDB(){
    this->fileName = "userdb.csv";
}

UserDB::UserDB(string filename){
    this->fileName = filename;
}

void UserDB::load() {
    ifstream DBFile(this->fileName);
    string line;

    while (getline(DBFile, line)) {
        stringstream ss(line);
        string idStr, username, display, encpass;

        if (getline(ss, idStr, ',') &&
            getline(ss, username, ',') &&
            getline(ss, display, ',') &&
            getline(ss, encpass)) {
            
            int id = std::stoi(idStr); // convert string to int
            userList[userCount++] = User(id, username, display, encpass);
        }
    }
}

void UserDB::save(){
    ofstream DBfile(this->fileName);
    for (int i=0 ; i < userCount ; i++){
        DBfile << userList[i].getID() << ',' 
        << userList[i].getUsername() << ',' 
        << userList[i].getDName() << ','
         << userList[i].getPass() << '\n';
    }
}

void UserDB::add(User user){
    userList[userCount++] = user;
    save();
}

void UserDB::printUserData(int id){
    bool found = false;
    for(int i=0 ; i < userCount ; i++){
        if(userList[i].getID() == id){
            userList[i].print();
            found = true;
        }
    }
    if (!found){
        cout << "not found";
    }
}


int UserDB::getNewID(){

    return userList[userCount-1].getID()+1;
}


bool UserDB::userNameAlreadyExist(string username){
    for (int i = 0; i < userCount; i++)
    {
        if(userList[i].getUsername() == username){
            return true;
        }
    }
    return false;
}

User* UserDB::findUserByUsername(string username) {
    for (int i = 0; i < userCount; i++) {
        if (userList[i].getUsername() == username) {
            return &userList[i];
        }
    }
    return nullptr;
}