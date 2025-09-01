#include "userutils.h"
#include <iomanip> //for time
#include <sstream>
bool UserUtils::isPassValid(string password) {
    bool isValidSize = false;
    bool hasNum = false;
    bool hasAlpha = false;

    if(password.size() >= 8 && password.size() <= 20) {
        isValidSize = true;
    }
    for (char c : password) {
        if (!isalnum(c))
            return false;
        if (isalpha(c))
            hasAlpha = true;
        if (isdigit(c))
            hasNum = true;
    }

    return isValidSize && hasNum && hasAlpha;
}

bool UserUtils::isUsernameValid(string username) {
    if (username.size() < 4 || username.size() > 15)
        return false;

    for (char c : username) {
        if (!isalnum(c))
            return false;
    }
    return true;
}


//timet is second from 1970 jan 1
string UserUtils::formatTimestamp(time_t time) {
    // "YYYY-MM-DD HH:MM:SS" is 19 characters, plus one for the null terminator.
    char buffer[20];
    std::tm* ptm = std::localtime(&time); // turns it into human readable time for the server locale
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ptm);
    return string(buffer); // turn into a string class
}