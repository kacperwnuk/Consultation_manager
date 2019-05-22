//
// Created by kacper on 20.04.2019.
//

#include "MessageSender.h"

void MessageSender::send(std::string message) {
    size_t size = message.size() + 4;
    char outMessage[size];
    snprintf(outMessage, size, "%04ld%s", message.size(), message.c_str());
    auto bytesToWrite = size;
    auto bytesWritten = 0;
    while (bytesWritten != bytesToWrite) {
        auto readStatus = write(socket, outMessage + bytesWritten, bytesToWrite - bytesWritten);
        if (readStatus != -1) {
            bytesWritten += readStatus;
        } else {
            // do something here
        }
    }
}

MessageSender::MessageSender(int socket): socket(socket) {

}
