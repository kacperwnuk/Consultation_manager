//
// Created by kacper on 10.04.2019.
//

#include "LoginResponse.h"

LoginResponse::LoginResponse(const StatusType &status):status(status) {

}

Json::Value LoginResponse::getJson() {

    Json::Value value;
    value["status"] = this->status;
    value["type"] = ResponseType::LoginResp;

    return value;
}


