#include "dec.h"

Decryption::Decryption(string text) {
    for(int i =0 ; i < static_cast<int>(text.size()) ; i++) {
        text[i] -= 2;
    }
    decText = text;
}