//
//
// Created by Marcin on 17.04.2019.

#include <sys/socket.h>
#include "ClientLogic.h"

void ClientLogic::run() {
    bool isRunning = true;
    while (isRunning) {

        Request* request = deserializer->getDeserializedObject();
        auto response = request->execute();
        std::cout<< response->getJson() << std::endl;
    }
}

ClientLogic::ClientLogic(int socket, MutualExclusiveHashMap<size_t> &readDemands,
                         const std::shared_ptr<SynchronizedQueue<OutgoingMessage>> &messageQueue) :
        socket(socket), readDemands(readDemands), messageQueue(messageQueue), dao("TIN") {

    auto clientMessageBuilder = std::make_shared<ClientMessageBuilder>(socket, readDemands);
    deserializer = std::make_unique<Deserializer>(clientMessageBuilder);
    serializer = std::make_unique<Serializer>();
}

std::shared_ptr<ClientMessageBuilder> ClientLogic::getClientMessageBuilder() {
    return deserializer->getClientMessageBuilder();
}




