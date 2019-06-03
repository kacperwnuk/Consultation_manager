//
// Created by root on 6/2/19.
//

#ifndef SERVER_AES256_H
#define SERVER_AES256_H

#include <stdio.h>
#include <string.h>

using namespace std;


//! AES256 class.
class AES256
{
public:
    static string encrypt(string text, string passphrase);
    static string decrypt(string text, string passphrase);

protected:
    static string encryptFinal(unsigned char *text, int text_len, unsigned char *key, unsigned char *iv);
    static string decryptFinal(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv);
};


#endif //SERVER_AES256_H
