//
// Created by root on 5/28/19.
//

#ifndef SERVER_RESERVATIONRESPONSE_H
#define SERVER_RESERVATIONRESPONSE_H


#include <jsoncpp/json/json.h>
#include "enums/StatusType.h"
#include "../serialization/Serializable.h"

class ReservationResponse : public Serializable {
    StatusType status;
public:
    explicit ReservationResponse(StatusType);

    Json::Value getJson() override;

};


#endif //SERVER_RESERVATIONRESPONSE_H
