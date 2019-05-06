//
//
// Created by Marcin on 17.04.2019.

#include <sys/socket.h>
#include "ClientLogic.h"
#include "../dto/enums/RequestType.h"
#include "../dto/ConsultationCancellationRequest.h"
#include "../dto/RegistrationRequest.h"
#include "../dto/RegistrationResponse.h"
#include "../dto/LoginResponse.h"
#include "../dto/DailyConsultationsListRequest.h"
#include "../entity/Consultation.h"

void ClientLogic::run() {
    bool isRunning = true;
    while (isRunning) {
        RequestType requestType = deserializer->getType();
        switch (requestType) {
            case RequestType::Login:
                gotLoginRequest();
                break;
            case RequestType::ConsultationCancellation:
                gotConsultationCancellationRequest();
                break;
            case RequestType::Registration:
                gotRegistrationRequest();
                break;
            case RequestType::DailyConsultationsList:
                gotDailyConsultationListRequest();
                break;
            default:
                break;
        }
    }
}

void ClientLogic::gotConsultationCancellationRequest() {
    std::cout << deserializer->deserializedObject<ConsultationCancellationRequest>()
            .getConsultationId().to_string() << std::endl;
}

void ClientLogic::gotLoginRequest() {
    auto loginRequest = deserializer->deserializedObject<LoginRequest>();
    std::cout << loginRequest << std::endl;
    auto status = tryToLogin(loginRequest);
    LoginResponse loginResponse(status);
    sendResponse(loginResponse);
}

void ClientLogic::gotRegistrationRequest() {
    auto registrationRequest = deserializer->deserializedObject<RegistrationRequest>();
    std::cout << registrationRequest << std::endl;
    auto status = tryToRegister(registrationRequest);
    RegistrationResponse registrationResponse(status);
    sendResponse(registrationResponse);
}

ClientLogic::ClientLogic(int socket, MutualExclusiveHashMap<size_t> &readDemands,
                         const std::shared_ptr<SynchronizedQueue<OutgoingMessage>> &messageQueue) :
        socket(socket), readDemands(readDemands), messageQueue(messageQueue), dao("TIN") {

    auto clientMessageBuilder = std::make_shared<ClientMessageBuilder>(socket, readDemands);
    deserializer = std::make_unique<Deserializer>(clientMessageBuilder);
    serializer = std::make_unique<Serializer>();
}

StatusType ClientLogic::tryToRegister(RegistrationRequest request) {
    auto account = Account(request.getEmail(), request.getLogin(), request.getPassword(), request.getName(),
                           request.getSurname(), request.getAccountRole(), AccountStatus::INACTIVE);
    auto document = account.getDocumentFormat();
    dao.setCollection("accounts");

    try {
        dao.insertDocument(document);
    }
    catch (std::exception &e) {
        std::cout << e.what();
        return ERROR;
    }
    std::cout << "Rejestracja pomyślna" << std::endl;
    return OK;
}


StatusType ClientLogic::tryToLogin(const LoginRequest &loginRequest) {
    dao.setCollection("accounts");
    try {
        auto account = dao.getAccountByLogin(loginRequest.getLogin());
        if (account.getPasswordHash() != loginRequest.getPassword()) {
            std::cout << "Bad passwd" << std::endl;
            return ERROR;
        }
    } catch (std::exception &e) {
        std::cout << e.what();
        return ERROR;
    }
    std::cout << "Logowanie pomyślne" << std::endl;
    return OK;
}

std::shared_ptr<ClientMessageBuilder> ClientLogic::getClientMessageBuilder() {
    return deserializer->getClientMessageBuilder();
}

void ClientLogic::gotDailyConsultationListRequest() {
    auto dailyConsultationsListRequest = deserializer->deserializedObject<DailyConsultationsListRequest>();
    getConsultations(dailyConsultationsListRequest.getDate());
}

std::vector<Consultation> ClientLogic::getConsultations(b_date date) {
    return std::vector<Consultation>();
}

