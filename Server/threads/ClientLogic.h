//
// Created by Marcin on 17.04.2019.
//

#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H


#include <string>
#include "Thread.h"
#include "../ClientMessageBuilder.h"
#include "../serialization/Deserializer.h"
#include "../dto/enums/StatusType.h"
#include "../dto/RegistrationRequest.h"
#include "../containers/OutgoingMessage.h"
#include "../serialization/Serializer.h"
#include "../Dao.h"
#include "../dto/LoginRequest.h"
#include "../entity/Consultation.h"
#include "../dto/NewConsultationRequest.h"
#include "../dto/DailyConsultationsListRequest.h"

class ClientLogic : public Thread {
    int socket;
    MutualExclusiveHashMap<size_t> &readDemands;
    Dao dao;
    std::shared_ptr<SynchronizedQueue<OutgoingMessage>> messageQueue;
    std::unique_ptr<Serializer> serializer;
    std::unique_ptr<Deserializer> deserializer;

    std::vector<ConsultationInfoForClient> tryToGetConsultations(DailyConsultationsListRequest dailyConsultationsListRequest);

    StatusType tryToRegister(RegistrationRequest);

    StatusType tryToLogin(LoginRequest);

    StatusType tryToAddConsultation(NewConsultationRequest);

    template<typename Request, typename ReturnType, typename Response>
    void handleRequest(std::function<ReturnType(ClientLogic*, Request)>);


public:


    ClientLogic(int socket, MutualExclusiveHashMap<size_t> &readDemands,
                const std::shared_ptr<SynchronizedQueue<OutgoingMessage>> &messageQueue);

    void run() override;

    template<typename T>
    void sendResponse(T);

    std::shared_ptr<ClientMessageBuilder> getClientMessageBuilder();
};

template<typename T>
void ClientLogic::sendResponse(T response) {
    auto output = serializer->serialize(response);
    OutgoingMessage outgoingMessage(socket, output.c_str(), output.length());
    messageQueue->put(outgoingMessage);

}


template<typename Request, typename ReturnType, typename Response>
void ClientLogic::handleRequest(std::function<ReturnType(ClientLogic*, Request)> tryHandleRequest) {
    Request request = deserializer->getDeserializedObject<Request>();
    Response response(tryHandleRequest(this, request));
    sendResponse(response);
}


#endif //SERVER_PARSER_H
