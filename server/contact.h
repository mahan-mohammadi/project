#include <string>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class Contact{
    public:

    Contact();
    Contact(string , string);
    Contact(json);

    string getUsername();
    string getDisplayName();
    string toString();
    private:
        string username;
        string DisplayName;
        
};