//
// Created by kacper on 17.04.2019.
//

#include "ClientMessageBuilder.h"

std::string ClientMessageBuilder::getMessage() {
    return getPayload(getHeader());
}

ClientMessageBuilder::ClientMessageBuilder(int socket) {
    this->socket = socket;
}

size_t ClientMessageBuilder::getHeader() {

    auto header = readBytes(4);
    return static_cast<size_t>(atoi(header.c_str()));
}

std::string ClientMessageBuilder::getPayload(size_t payloadSize) {
    return readBytes(payloadSize);
}

std::string ClientMessageBuilder::readBytes(size_t bytesToRead) {
    size_t bytesRead = 0;
    char payload[bytesToRead];
    while (bytesRead != bytesToRead) {
        auto readStatus = read(socket, payload + bytesRead, bytesToRead - bytesRead);
        if (readStatus > 0) {
            bytesRead += readStatus;
        } else {
            std::cout << "read exception" << std::endl;
            throw ReadException();
        }
    }
    return payload;
}


const char *ClientMessageBuilder::ReadException::what() const noexcept {
    return "read exception";
}
