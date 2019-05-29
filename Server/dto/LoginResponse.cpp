//
// Created by kacper on 10.04.2019.
//

#include "LoginResponse.h"

LoginResponse::LoginResponse(const StatusType &status):status(status) {

}

LoginResponse::LoginResponse(const StatusType &status, const AccountRole &role):status(status),role(role) {

}

Json::Value LoginResponse::getJson() {

    Json::Value value;
    value["status"] = this->status;
    value["type"] = "LoginResponse";
    value["role"] = this->role;

    return value;
}


