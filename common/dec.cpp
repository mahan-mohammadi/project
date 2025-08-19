#include "dec.h"

Decryption::Decryption(string text) {
    // the the.size output is in size_t not int
    for(int i =0 ; i < static_cast<int>(text.size()) ; i++) {
        text[i] -= 2;
    }
    decText = text;
}