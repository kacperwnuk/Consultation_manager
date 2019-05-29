//
// Created by slawek on 29.05.19.
//

#include "CancelConsultationResponse.h"

CancelConsultationResponse::CancelConsultationResponse(StatusType status) : status(status) {

}


Json::Value CancelConsultationResponse::getJson() {
    Json::Value value;
    value["status"] = this->status;
    value["type"] = "CancelConsultationResponse";
    return value;
}