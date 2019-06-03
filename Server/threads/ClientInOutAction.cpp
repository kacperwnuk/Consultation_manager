//
// Created by Marcin on 14.05.2019.
//

#include "ClientInOutAction.h"
#include <string>
#include <iostream>


void ClientInOutAction::send(std::string key) {

    if (!writing) {
        auto response = outQueue.get();
        message = serializer.serialize(std::move(response));
        std::string encryptedMessage = encryption.encrypt(message, key);
        char s[encryptedMessage.size() + 4];
        sprintf(s, "%04lu%s", encryptedMessage.size(), encryptedMessage.c_str());
        message = s;
        bytesToWrite = sizeof(s);
        bytesWritten = 0;
        writing = !writing;
    }

    auto status = write(fd, message.c_str() + bytesWritten, bytesToWrite);
    if (status != -1) {
        bytesWritten += status;
    }

    if (bytesWritten == bytesToWrite) {
        writing = !writing;
//        wantsToWrite =  false;

    }
}

void ClientInOutAction::receive(std::string key) {

    if (!readingHeader && !payloadAllocated) {
        payloadAllocated = true;
        payload = new char[bytesToRead];
    }

    auto status = read(fd, readingHeader ? header + bytesRead : payload + bytesRead, bytesToRead - bytesRead);
    if (status > 0) {
        bytesRead += status;
    } else if (status == 0) {
        std::cout << "Disconnected user ;<" << std::endl;
        connected = false;
    } else if (status == -1) {
        std::cout << "Error!" << std::endl;
    }

    if (readingHeader && bytesToRead == bytesRead) {
        readingHeader = false;
        bytesRead = 0;
        bytesToRead = strtol(header, NULL, 10);
    }

    if (!readingHeader && bytesToRead == bytesRead) {
        readingHeader = true;
        std::string stringPayload(payload);
        std::string toDecrypt = stringPayload.substr(0, bytesToRead);
        std::string decryptedPayload = encryption.decrypt(toDecrypt, key);
        std::cout << "Zdeszyfrowana wiadomosc otrzymana: " << decryptedPayload << std::endl;

        auto request = deserializer.getDeserializedObject(decryptedPayload);
        if (request != nullptr) {
            inQueue.put(std::move(request));
        }
        bytesToRead = 4;
        bytesRead = 0;
        payloadAllocated = false;
    }

}

ClientInOutAction::ClientInOutAction(int fd, SynchronizedQueue<std::unique_ptr<Request>> &inQueue,
                                     SynchronizedQueue<std::unique_ptr<Serializable>> &outQueue, bool &wantsToWrite, bool &connected)
        : inQueue(inQueue), outQueue(outQueue), wantsToWrite(wantsToWrite), connected(connected) {
    this->fd = fd;
}

