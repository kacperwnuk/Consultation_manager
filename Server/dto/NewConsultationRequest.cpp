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



Request *NewConsultationRequest::create(Json::Value value) {
    return new NewConsultationRequest(value);
}

Serializable *NewConsultationRequest::execute() {

    auto dao = Dao::getDaoCollection("TIN", "consultation");
    auto consultationStart = getConsultationDateStart();
    auto consultationEnd = getConsultationDateEnd();

    if (consultationStart >= consultationEnd){
        //Consultaton start after end!
        return new NewConsultationResponse(ERROR);
    }
    auto consultations = dao->getConsultationsByDate(consultationStart, consultationEnd);
    if (!consultations.empty()){
        //There is another consultation in this time!
        return new NewConsultationResponse(ERROR);
    }
    Consultation consultation = Consultation(getConsultationInfo(), ConsultationStatus::FREE);
    auto document = consultation.getDocumentFormat();
    try {
        dao->insertDocument(document);
    } catch (std::exception &e) {
        std::cout << e.what();
        return new NewConsultationResponse(ERROR);
    }
    return new NewConsultationResponse(OK);
}

