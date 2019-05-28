//
// Created by root on 5/28/19.
//

#include "ReservationResponse.h"

ReservationResponse::ReservationResponse(StatusType status) : status(status) {

}


Json::Value ReservationResponse::getJson() {
    Json::Value value;
    value["status"] = this->status;
    value["type"] = "ReservationResponse";
    return value;
}
