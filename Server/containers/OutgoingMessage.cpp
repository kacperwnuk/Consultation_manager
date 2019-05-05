//
// Created by Marcin on 04.04.2019.
//

#include <cstring>
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "OutgoingMessage.h"

OutgoingMessage::OutgoingMessage(int fd, const char *payload, unsigned long size): fd(fd), size(size) {
    this->payload = new char[size + 4];
    this->size += 4;

    std::string payloadSize = std::to_string(size);
    auto amountOfZerosNeeded = 4 - payloadSize.length();
    char* zeros = new char[amountOfZerosNeeded];
    std::fill_n(zeros, amountOfZerosNeeded, '0');

    strcpy(this->payload, zeros);
    strcpy(this->payload + amountOfZerosNeeded, payloadSize.c_str());
    strcpy(this->payload + 4, payload);
}

OutgoingMessage::OutgoingMessage() {

}
