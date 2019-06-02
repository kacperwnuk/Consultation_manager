//
// Created by root on 6/2/19.
//

#include "Encryption.h"

const string &Encryption::getKey() const {
    return key;
}

void Encryption::setKey(const string &key) {
    Encryption::key = key;
}

string Encryption::encrypt(string message) {
    return aes.encrypt(message, key);
}

string Encryption::decrypt(string message) {
    return aes.decrypt(message, key);
}


