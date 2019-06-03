//
// Created by root on 6/2/19.
//

#include "Encryption.h"
#include "security/base64.h"
#include <iostream>

/*
const string &Encryption::getKey() const {
    return key;
}

void Encryption::setKey(const string &key) {
    Encryption::key = key;
} */

string Encryption::encrypt(string toEncrypt, string key) {

    string output = toEncrypt;
    for (int i = 0; i < toEncrypt.length(); i++)
        output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
    return base64_encode((const unsigned char*)output.c_str(), output.length());
}

string Encryption::decrypt(string message, string key) {
    return aes.decrypt(message, key);
}


