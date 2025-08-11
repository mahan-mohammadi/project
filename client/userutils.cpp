#include "userutils.h"

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
        if (isdigit(static_cast<unsigned char>(c)))
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