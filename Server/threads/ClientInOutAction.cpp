//
// Created by Marcin on 14.05.2019.
//

#include "ClientInOutAction.h"

void ClientInOutAction::send() {

    if (!writing) {
        std::cout << "getting ittem" << std::endl;
        auto *response = outQueue.get();
        std::cout << "got item" << std::endl;
        message = serializer.serialize(response);
//        delete response;
        bytesToWrite = message.size();
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

void ClientInOutAction::receive() {

    if (!readingHeader && !payloadAllocated) {
        payloadAllocated = true;
        payload = new char[bytesToRead];
    }

    auto status = read(fd, readingHeader? header + bytesRead : payload + bytesRead, bytesToRead - bytesRead);
    if (status != -1) {
        bytesRead += status;
    }

    if (readingHeader && bytesToRead == bytesRead) {
        readingHeader = false;
        bytesRead = 0;
        bytesToRead = atoi(header);
    }

    if (!readingHeader && bytesToRead == bytesRead) {
        readingHeader = true;
        auto *request = deserializer.getDeserializedObject(payload);
        inQueue.put(request);
        bytesToRead = 4;
        bytesRead = 0;
//        delete[] payload;
    }

}


ClientInOutAction::ClientInOutAction(int fd, SynchronizedQueue<Request *> &inQueue,
                                     SynchronizedQueue<Serializable *> &outQueue, bool& wantsToWrite, bool &connected)
        : inQueue(inQueue), outQueue(outQueue), wantsToWrite(wantsToWrite), connected(connected) {
    this->fd = fd;
}

