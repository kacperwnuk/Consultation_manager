//
// Created by kacper on 10.04.2019.
//

#include "ConsultationCancellationRequest.h"

ConsultationCancellationRequest::ConsultationCancellationRequest(Json::Value jsonValue) {

    this->consultationId = oid(jsonValue["_id"].asString());
}

const oid &ConsultationCancellationRequest::getConsultationId() const {
    return consultationId;
}