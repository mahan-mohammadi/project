#include <string>
#include "json.hpp"
#include "contact.h"

using json = nlohmann::json;
using namespace std;

class ContactsDB{
    public:
        ContactsDB();
        ContactsDB(string);
        void addContact(Contact);
        json getContactsJson(int userId);

    private:
        string filename;
        json contacts;
        void load();
        void save() const;

};