#include "dec.h"

Decryption::Decryption(string text){
    for(int i =0 ; i < text.size() ; i++){
        text[i] -= 2;
    }
    decText = text;
}