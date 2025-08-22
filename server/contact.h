#ifndef CONTACT_H // "If USER_H has not been defined yet..."
#define CONTACT_H

#include <string>
#include "json.hpp"
#include "user.h"

using json = nlohmann::json;
using namespace std;

class Contact {
public:

    Contact();
    Contact(User);
    Contact(string, string);
    Contact(json);

    string getUsername();
    string getDisplayName();
    int getID();
    string toString();
    json toJson();
private:
    int id;
    string username;
    string displayName;

};

#endif