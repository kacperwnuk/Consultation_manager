//
// Created by Marcin on 17.04.2019.
//

#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H


#include <string>
#include "Thread.h"
#include "ClientMessageBuilder.h"
#include "serialization/Deserializer.h"
#include "dto/enums/StatusType.h"
#include "dto/RegistrationRequest.h"
#include "containers/OutgoingMessage.h"
#include "serialization/Serializer.h"
#include "Dao.h"
#include "dto/LoginRequest.h"

class ClientLogic: public Thread {
    int socket;
    MutualExclusiveHashMap<size_t> &readDemands;
    Dao dao;
    std::shared_ptr<SynchronizedQueue<OutgoingMessage>> messageQueue;
    std::unique_ptr<Serializer> serializer;
public:
    std::unique_ptr<Deserializer> deserializer;

    ClientLogic(int socket, MutualExclusiveHashMap<size_t> &readDemands,
                const std::shared_ptr<SynchronizedQueue<OutgoingMessage>> &messageQueue);

    void run() override;
    StatusType tryToRegister(RegistrationRequest);
    StatusType tryToLogin(const LoginRequest&);

    template <typename T>
    void sendResponse(T);
};

template<typename T>
void ClientLogic::sendResponse(T response) {
    auto output = serializer->serialize(response);
    OutgoingMessage outgoingMessage(socket, output.c_str(), output.length());
    messageQueue->put(outgoingMessage);

}



#endif //SERVER_PARSER_H
