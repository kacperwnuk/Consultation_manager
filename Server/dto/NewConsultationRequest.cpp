//
// Created by kacper on 07.05.2019.
//

#include <iostream>
#include "NewConsultationRequest.h"
#include "NewConsultationResponse.h"

NewConsultationRequest::NewConsultationHelper NewConsultationRequest::newConsultationHelper;

NewConsultationRequest::NewConsultationRequest(Json::Value jsonValue) : consultationDateStart(
        std::chrono::system_clock::now()), consultationDateEnd(std::chrono::system_clock::now()) {
    this->room = jsonValue["room"].asString();
    this->consultationTutorLogin = jsonValue["tutor"].asString();
    this->consultationDateStart = b_date(std::chrono::milliseconds(jsonValue["consultationDateStart"].asLargestUInt()));
    this->consultationDateEnd = b_date(std::chrono::milliseconds(jsonValue["consultationDateEnd"].asLargestUInt()));
}

std::ostream &operator<<(std::ostream &os, const NewConsultationRequest &request) {
    os << "consultation: " << request.consultationCreatorLogin << "room" << request.room << "consultationType"
       << request.consultationType;
    return os;
}

std::unique_ptr<Request> NewConsultationRequest::create(Json::Value value) {
    std::unique_ptr<Request> request(new NewConsultationRequest(value));
    return std::move(request);
}

std::unique_ptr<Serializable> NewConsultationRequest::execute(Context& context) {

    if (!context.isLogged()){
        std::unique_ptr<Serializable> response (new NewConsultationResponse(ERROR));
        return std::move(response);
    }

    this->consultationCreatorLogin = context.getLogin();
    this->consultationType = context.getAccountRole() == LECTURER ? LECTURER_SUGGESTED : STUDENT_SUGGESTED;

    auto accountDao = Dao::getDaoCollection("TIN", "account");

    try {
        auto account = accountDao->getAccountByLogin(this->consultationCreatorLogin);
        AccountInfoForClient accountInfoForClient(account);


        auto collectionDao = Dao::getDaoCollection("TIN", "consultation");
        auto consultationStart = this->consultationDateStart;
        auto consultationEnd = this->consultationDateEnd;

        if (consultationStart >= consultationEnd) {
            //Consultaton start after end!
            std::unique_ptr<Serializable> response(new NewConsultationResponse(ERROR));
            return std::move(response);
        }
        auto consultations = collectionDao->getConsultationsByDate(consultationStart, consultationEnd);
        if (!consultations.empty()) {
            //There is another consultation in this time!
            std::unique_ptr<Serializable> response(new NewConsultationResponse(ERROR));
            return std::move(response);
        }

        auto accountTutor = context.getAccountRole() == STUDENT ? accountDao->getAccountByLogin(this->consultationTutorLogin) : context.getAccount();
        AccountInfoForClient accountInfoForClientTutor(accountTutor);

        auto accountStudent = accountDao->getAccountByLogin(this->consultationCreatorLogin);
        AccountInfoForClient accountInfoForClientStudent(account);

        ConsultationInfoForClient consultationInfo(this->id.to_string(), accountInfoForClientTutor, accountInfoForClientStudent,
                                                   this->consultationDateStart, this->consultationDateEnd, this->room,
                                                   this->consultationType);


        Consultation consultation;
        if (context.getAccountRole() == AccountRole::LECTURER) {
            consultation = Consultation(consultationInfo, ConsultationStatus::FREE);
        } else {
            consultation = Consultation(consultationInfo, ConsultationStatus::AWAITING_LECTURER_CONFIRMATION);
        }


        auto document = consultation.getDocumentFormat();
        collectionDao->insertDocument(document);
    } catch (std::exception &e) {
        std::cout << e.what();
        std::unique_ptr<Serializable> response(new NewConsultationResponse(ERROR));
        return std::move(response);
    }
    std::unique_ptr<Serializable> response(new NewConsultationResponse(OK));
    return std::move(response);
}

NewConsultationRequest::NewConsultationRequest() : consultationDateStart(std::chrono::system_clock::now()),
                                                   consultationDateEnd(std::chrono::system_clock::now()) {

}

