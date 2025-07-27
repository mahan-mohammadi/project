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
    int i = 0;

    while (getline(DBFile, line)) {
        stringstream ss(line);
        string idStr, username, display, encpass;

        if (getline(ss, idStr, ',') &&
            getline(ss, username, ',') &&
            getline(ss, display, ',') &&
            getline(ss, encpass)) {
            
            int id = std::stoi(idStr); // convert string to int
            userList[i] = User(id, username, display, encpass);
            i++;
        }
    }
}
