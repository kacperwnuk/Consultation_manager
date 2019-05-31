//
// Created by slawek on 31.05.19.
//

#include "AcceptConsultationResponse.h"

AcceptConsultationResponse::AcceptConsultationResponse(StatusType status) : status(status) {

}


Json::Value AcceptConsultationResponse::getJson() {
    Json::Value value;
    value["status"] = this->status;
    value["type"] = "AcceptConsultationResponse";
    return value;
}