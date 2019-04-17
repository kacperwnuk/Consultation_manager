//
// Created by kacper on 17.04.2019.
//

#include "ClientMessageBuilderThread.h"

void ClientMessageBuilderThread::run() {
    auto messageSize = 0;
    auto isRunning = true;
    while(isRunning){
        auto messageChunk = (*messageBuffer).get();
        if(!duringBuilding){
            char payloadSize[4];
            strncpy(payloadSize, messageChunk.payload, 4);
            messageSize = atoi(payloadSize);
            std::cout<<messageSize<<std::endl;
            duringBuilding = true;

        }
    }
}

ClientMessageBuilderThread::ClientMessageBuilderThread(int socket, std::shared_ptr<SynchronizedQueue<IncomingMessage>> clientMessageBuffer) {
    this->socket = socket;
    this->messageBuffer = clientMessageBuffer;
}
