#include <iostream>
#include <string>
#include "user.h"

using namespace std;

class UserDB{
    private:
        string fileName;
        User userList[];
    public:
        UserDB();
        UserDB(string);
        void load();
        void save();
        void add(User);
        void remove(int);
        void edit(int , User);
        void printUserData(int);   
};