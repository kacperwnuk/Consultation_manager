//
// Created by slawek on 31.05.19.
//

#include "RejectAccountsResponse.h"

RejectAccountsResponse::RejectAccountsResponse(StatusType status) : status(status) {

}

Json::Value RejectAccountsResponse::getJson() {
    Json::Value value;
    value["status"] = this->status;
    value["type"] = "RejectAccountsResponse";
    return value;
}