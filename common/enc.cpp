#include "enc.h"

Encryption::Encryption(string text) {
    for(int i =0 ; i < static_cast<int>(text.size()) ; i++) {
        text[i] += 2;
    }
    encPass = text;
}

string Encryption::getEncText() {
    return encPass;
}