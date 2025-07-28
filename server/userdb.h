#include <iostream>
#include <string>
#include "user.h"

using namespace std;

class UserDB{
    private:
        string fileName;
        User userList[1000];
        int userCount =0;
    public:
        UserDB();
        UserDB(string);
        void load();
        void save();
        void add(User);
        void printUserData(int);
        int getNewID();
};