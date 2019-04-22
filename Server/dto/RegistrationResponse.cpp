//
// Created by kacper on 20.04.2019.
//

#include <iostream>
#include "RegistrationResponse.h"

Json::Value RegistrationResponse::getJson() {

    Json::Value value;
    value["status"] = this->status;
    return value;
}

RegistrationResponse::RegistrationResponse(StatusType status) : status(status) {

}
