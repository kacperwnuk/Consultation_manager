//
// Created by Marcin on 04.04.2019.
//

#include "OutgoingMessage.h"

OutgoingMessage::OutgoingMessage(int fd, const char *payload, int size): fd(fd), size(size) {
    std::copy(payload, payload + size, this->payload);
}

OutgoingMessage::OutgoingMessage() {

}
