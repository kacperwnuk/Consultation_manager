//
//
// Created by Marcin on 17.04.2019.

#include <sys/socket.h>
#include "ClientLogic.h"

void ClientLogic::run() {
    bool isRunning = true;
    while (isRunning) {

        Request* request = inQueue.get();
        auto response = request->execute();
        std::cout << response->getJson() << std::endl;
        outQueue.put(response);
    }
}

ClientLogic::ClientLogic(SynchronizedQueue<Request*> &inQueue, SynchronizedQueue<Serializable*> &outQueue, bool &readyToSend): inQueue(inQueue), outQueue(outQueue), readyToSend(readyToSend) {

}

