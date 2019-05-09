//
// Created by kacper on 07.05.2019.
//

#include "NewConsultationRequest.h"

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

