//
// Created by kacper on 20.04.2019.
//

#ifndef SERVER_REGISTRATIONRESPONSE_H
#define SERVER_REGISTRATIONRESPONSE_H


#include "enums/StatusType.h"
#include "../serialization/Serializable.h"

class RegistrationResponse : public Serializable {
    StatusType status;
public:
    RegistrationResponse(StatusType);

    Json::Value getJson() override;
};


#endif //SERVER_REGISTRATIONRESPONSE_H
