//
// Created by root on 6/2/19.
//

#ifndef SERVER_ENCRYPTION_H
#define SERVER_ENCRYPTION_H
#include <string>
#include "security/aes256.h"
using namespace std;

class Encryption {
private:
    AES256 aes;
    //string key = "adamsobieski1234adamsobieski1234";

public:
    //const string &getKey() const;

    //void setKey(const string &key);

public:
    string encrypt(string message,string key);
    string decrypt(string message,string key);
};


#endif //SERVER_ENCRYPTION_H
