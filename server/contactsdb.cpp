#include "contactsdb.h"
#include <fstream>

ContactsDB::ContactsDB(){
    filename = "contacts.json";
    load();
}

ContactsDB::ContactsDB(string filename){
    this->filename = filename;
    load();
}

void ContactsDB::load() {
    ifstream file(filename);
    
    if(file.good())
        file >> contactslist;
    else
        contactslist = json::object();
}

void ContactsDB::save() {
    ofstream file(filename);
    file << contactslist.dump(2);
}

void ContactsDB::addContact(int forUserId, User contactToAdd) {
    string userIdStr = to_string(forUserId);

    if (!contactslist.contains(userIdStr)) {
        contactslist[userIdStr] = json::array();
    }

    bool exists = false;
    for (const auto& contactJson : contactslist[userIdStr]) {
        if (contactJson.at("id").get<int>() == contactToAdd.getID()) {
            exists = true;
            break;
        }
    }

    if (!exists) {
        Contact newContact(contactToAdd);
        contactslist[userIdStr].push_back(newContact.toJson());
        save();
}
}

json ContactsDB::getContactsJson(int userid) {
    string userIdStr = to_string(userid);

    if (contactslist.contains(userIdStr)) {
        return contactslist[userIdStr];
    }

    return json::array();
}