#include "userutils.h"



//rewrite so password and username are also alphanum only

bool UserUtils::isPassValid(string password){
    bool isValidSize = false;
    bool hasNum = false;
    bool hasAlpha = false;

    if(password.size() >= 8 && password.size() <= 20){
        isValidSize = true;
    }
    for(char c : password){
        if(isalpha(c)){
            hasAlpha = true;
            break;
        }
    }
    for(char c : password){
        if(isdigit(c)){
            hasNum = true;
            break;
        }
    }
    return isValidSize && hasNum && hasAlpha;
}

bool UserUtils::isUsernameValid(string username){
    if(username.size() >= 4 && username.size() <= 15){
        return true;
    }
    else{
        return false;
    }
}