//
// Created by kacper on 07.05.2019.
//

#include "NewConsultationRequest.h"

NewConsultationRequest::NewConsultationRequest(Json::Value jsonValue): consultation(Consultation(std::move(jsonValue))) {

}

std::ostream &operator<<(std::ostream &os, const NewConsultationRequest &request) {
    os << "consultation: " << request.consultation;
    return os;
}

bsoncxx::document::view_or_value NewConsultationRequest::getConsultationDocumentFormat() {
    return consultation.getDocumentFormat();
}
