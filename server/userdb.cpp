#include "userdb.h"
#include <fstream>

UserDB::UserDB(){
    this->fileName = "userdb.csv";
}

UserDB::UserDB(string filename){
    this->fileName = filename;
}

