//
// Created by kacper on 07.05.2019.
//

#include "NewConsultationResponse.h"
#include "enums/ResponseType.h"

NewConsultationResponse::NewConsultationResponse(StatusType statusType) : statusType(statusType) {}

Json::Value NewConsultationResponse::getJson() {
    Json::Value value;
    value["status"] = this->statusType;
    value["type"] = ResponseType::NewConsultationLecturerResp;

    return value;
}
