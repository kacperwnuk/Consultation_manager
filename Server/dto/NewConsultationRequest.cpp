//
// Created by kacper on 07.05.2019.
//

#include <iostream>
#include "NewConsultationRequest.h"
#include "NewConsultationResponse.h"

NewConsultationRequest::NewConsultationHelper NewConsultationRequest::newConsultationHelper;

NewConsultationRequest::NewConsultationRequest(Json::Value jsonValue): consultationInfo(ConsultationInfoForClient(std::move(jsonValue))) {

}

std::ostream &operator<<(std::ostream &os, const NewConsultationRequest &request) {
    os << "consultation: " << request.consultationInfo;
    return os;
}

const ConsultationInfoForClient &NewConsultationRequest::getConsultationInfo() const {
    return consultationInfo;
}

b_date NewConsultationRequest::getConsultationDateStart() {
    return this->consultationInfo.getConsultationDateStart();
}

b_date NewConsultationRequest::getConsultationDateEnd() {
    return this->consultationInfo.getConsultationDateEnd();

}



std::unique_ptr<Request> NewConsultationRequest::create(Json::Value value) {
    std::unique_ptr<Request> request (new NewConsultationRequest(value));
    return std::move(request);
}

std::unique_ptr<Serializable> NewConsultationRequest::execute() {

    auto dao = Dao::getDaoCollection("TIN", "consultation");
    auto consultationStart = getConsultationDateStart();
    auto consultationEnd = getConsultationDateEnd();

    if (consultationStart >= consultationEnd){
        //Consultaton start after end!
        std::unique_ptr<Serializable> response(new NewConsultationResponse(ERROR));
        return std::move(response);
    }
    auto consultations = dao->getConsultationsByDate(consultationStart, consultationEnd);
    if (!consultations.empty()){
        //There is another consultation in this time!
        std::unique_ptr<Serializable> response(new NewConsultationResponse(ERROR));
        return std::move(response);
    }
    Consultation consultation = Consultation(getConsultationInfo(), ConsultationStatus::FREE);
    auto document = consultation.getDocumentFormat();
    try {
        dao->insertDocument(document);
    } catch (std::exception &e) {
        std::cout << e.what();
        std::unique_ptr<Serializable> response(new NewConsultationResponse(ERROR));
        return std::move(response);
    }
    std::unique_ptr<Serializable> response(new NewConsultationResponse(OK));
    return std::move(response);
}

