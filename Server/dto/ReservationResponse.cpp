//
// Created by kacper on 10.04.2019.
//

#include "ReservationResponse.h"

ReservationResponse::ReservationResponse(const StatusType &status) : status(status) {

}

Json::Value ReservationResponse::getJson() {

    Json::Value value;
    value["status"] = this->status;

    return value;
}
