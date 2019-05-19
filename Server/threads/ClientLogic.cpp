//
//
// Created by Marcin on 17.04.2019.

#include <sys/socket.h>
#include <iostream>
#include "ClientLogic.h"

void ClientLogic::run() {
    bool isRunning = true;
    while (isRunning) {

        auto request = inQueue.get();
        auto response = request->execute();
        std::cout << response->getJson() << std::endl;
        outQueue.put(std::move(response));
        std::cout<<write(pipe, "a", 1)<<std::endl;
    }
}

ClientLogic::ClientLogic(SynchronizedQueue<std::unique_ptr<Request>> &inQueue, SynchronizedQueue<std::unique_ptr<Serializable>> &outQueue, bool &readyToSend, int pipefd): inQueue(inQueue), outQueue(outQueue), readyToSend(readyToSend), pipe(pipefd) {

}

