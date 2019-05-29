//
// Created by slawek on 29.05.19.
//

#include "AcceptAccountsResponse.h"

AcceptAccountsResponse::AcceptAccountsResponse(StatusType status) : status(status) {

}


Json::Value AcceptAccountsResponse::getJson() {
    Json::Value value;
    value["status"] = this->status;
    value["type"] = "AcceptAccountsResponse";
    return value;
}