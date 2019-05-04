//
// Created by kacper on 10.04.2019.
//

#include <iostream>
#include "ConsultationCancellationRequest.h"

ConsultationCancellationRequest::ConsultationCancellationRequest(Json::Value jsonValue) {
    std::cout << jsonValue.toStyledString() << std::endl;
    this->consultationId = oid(jsonValue["_id"].asString());
}

const oid &ConsultationCancellationRequest::getConsultationId() const {
    return consultationId;
}