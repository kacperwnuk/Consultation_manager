//
// Created by slawek on 31.05.19.
//

#include "RejectConsultationResponse.h"

RejectConsultationResponse::RejectConsultationResponse(StatusType status) : status(status) {

}


Json::Value RejectConsultationResponse::getJson() {
    Json::Value value;
    value["status"] = this->status;
    value["type"] = "RejectConsultationResponse";
    return value;
}