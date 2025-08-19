#include "userutils.h"
#include <iomanip>
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

string UserUtils::formatTimestamp(time_t time){
    std::tm* ptm = std::localtime(&time);
    std::stringstream ss;
    ss << std::put_time(ptm, "%Y-%m-%d %H:%M:%S"); //YYYY-MM-DD HH:MM:SS
    return ss.str();
}