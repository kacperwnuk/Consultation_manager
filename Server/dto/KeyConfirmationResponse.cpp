//
// Created by root on 6/3/19.
//

#include "KeyConfirmationResponse.h"

KeyConfirmationResponse::KeyConfirmationResponse(StatusType toStatus): status(toStatus) {

}

Json::Value KeyConfirmationResponse::getJson() {
    Json::Value value;
    value["status"] = this->status;
    value["type"] = "KeyConfirmationResponse";
    return value;}

