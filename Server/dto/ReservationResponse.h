//
// Created by kacper on 10.04.2019.
//

#ifndef SERVER_RESERVATIONRESPONSE_H
#define SERVER_RESERVATIONRESPONSE_H


#include "enums/StatusType.h"
#include "../serialization/Serializable.h"

class ReservationResponse : public Serializable {
private:
    StatusType status;
public:
    explicit ReservationResponse(const StatusType &);

    Json::Value getJson() override;
};


#endif //SERVER_RESERVATIONRESPONSE_H
