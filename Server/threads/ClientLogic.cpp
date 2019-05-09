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
#include "../dto/NewConsultationRequest.h"
#include "../dto/NewConsultationResponse.h"
#include "../dto/DailyConsultationsListResponse.h"

void ClientLogic::run() {
    bool isRunning = true;
    while (isRunning) {
        RequestType requestType = deserializer->getType();
        switch (requestType) {
            case RequestType::Login:
                handleRequest<LoginRequest, StatusType, LoginResponse>(&ClientLogic::tryToLogin);
                break;
            case RequestType::ConsultationCancellation:
                break;
            case RequestType::Registration:
                handleRequest<RegistrationRequest, StatusType, RegistrationResponse>(&ClientLogic::tryToRegister);
                break;
            case RequestType::DailyConsultationsList:
                handleRequest<DailyConsultationsListRequest, std::vector<ConsultationInfoForClient>, DailyConsultationsListResponse>(
                        &ClientLogic::tryToGetConsultations);
                break;
            case RequestType::NewConsultationLecturer:
                handleRequest<NewConsultationRequest, StatusType, NewConsultationResponse>(&ClientLogic::tryToAddConsultation);
                break;
            default:
                break;
        }
    }
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
    dao.setCollection("account");

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


StatusType ClientLogic::tryToLogin(LoginRequest loginRequest) {
    dao.setCollection("account");
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

StatusType ClientLogic::tryToAddConsultation(NewConsultationRequest newConsultationRequest) {
    dao.setCollection("consultation");

    auto consultationStart = newConsultationRequest.getConsultationDateStart();
    auto consultationEnd = newConsultationRequest.getConsultationDateEnd();

    if (consultationStart >= consultationEnd){
        //Consultaton start after end!
        return ERROR;
    }
    auto consultations = dao.getConsultationsByDate(consultationStart, consultationEnd);
    if (!consultations.empty()){
        //There is another consultation in this time!
        return ERROR;
    }
    Consultation consultation = Consultation(newConsultationRequest.getConsultationInfo(), ConsultationStatus::FREE);
    auto document = consultation.getDocumentFormat();
    try {
        dao.insertDocument(document);
    } catch (std::exception &e) {
        std::cout << e.what();
        return ERROR;
    }
    return OK;
}


std::shared_ptr<ClientMessageBuilder> ClientLogic::getClientMessageBuilder() {
    return deserializer->getClientMessageBuilder();
}


std::vector<ConsultationInfoForClient> ClientLogic::tryToGetConsultations(DailyConsultationsListRequest dailyConsultationsListRequest) {
    dao.setCollection("consultation");

    auto today = dailyConsultationsListRequest.getDate();
    auto tomorrow = b_date(std::chrono::milliseconds(today.value.count() + std::chrono::milliseconds(std::chrono::hours(24)).count()));
    auto consultations = dao.getConsultationsByDate(today, tomorrow);

    return consultations;
}





