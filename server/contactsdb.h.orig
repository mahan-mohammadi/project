#include <string>
#include "json.hpp"
#include "contact.h"
#include "user.h"
using json = nlohmann::json;
using namespace std;

class ContactsDB{
    public:
        ContactsDB();
        ContactsDB(string);
        void addContact(int , User);
        json getContactsJson(int);

    private:
        string filename;
        json contactslist;
        void load();
        void save();

};