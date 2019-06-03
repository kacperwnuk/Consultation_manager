//
// Created by root on 6/2/19.
//

#include "Encryption.h"
#include "security/base64.h"
#include <iostream>

const string &Encryption::getKey() const {
    return key;
}

void Encryption::setKey(const string &key) {
    Encryption::key = key;
}

string Encryption::encrypt(string toEncrypt) {
    //string key1 = "ABC"; //Any chars will work
    //const char * key = key1.c_str();
    char key[8] = {'A', 'B', 'C', '1', '2', '3', 'E', 'F'};
    std::cout << "SZYFRUJE WIADOMOSC: " << toEncrypt << std::endl;
    string output = toEncrypt;

    for (int i = 0; i < toEncrypt.length(); i++)
        output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

    std::cout << "Przed basem:" << std::endl;
    for(int i=0; i < output.length(); ++i)
        std::cout <<  (int)output[i] << " ";
    //return output;
    std::cout << std::endl;
    return base64_encode((const unsigned char*)output.c_str(), output.length());

}

string Encryption::decrypt(string message) {
    return aes.decrypt(message, key);
}


