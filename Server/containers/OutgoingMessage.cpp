//
// Created by Marcin on 04.04.2019.
//

#include <cstring>
#include "OutgoingMessage.h"

OutgoingMessage::OutgoingMessage(int fd, const char *payload, int size): fd(fd), size(size) {
    this->payload = new char[size + 1];
    strcpy(this->payload, payload);
}

OutgoingMessage::OutgoingMessage() {

}
