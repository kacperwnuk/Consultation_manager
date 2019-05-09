//
// Created by Marcin on 04.04.2019.
//

#include <cstring>
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "OutgoingMessage.h"

OutgoingMessage::OutgoingMessage(int fd, const char *payload, unsigned long payloadSize): fd(fd), size(payloadSize + 4) {
    this->payload = new char[this->size];

    snprintf(this->payload, this->size,"%04ld%s", payloadSize, payload);
}

OutgoingMessage::OutgoingMessage() {

}
