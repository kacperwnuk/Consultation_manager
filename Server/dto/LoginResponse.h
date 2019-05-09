//
// Created by kacper on 10.04.2019.
//

#ifndef SERVER_LOGINRESPONSE_H
#define SERVER_LOGINRESPONSE_H


#include "enums/StatusType.h"
#include "enums/ResponseType.h"
#include "../serialization/Serializable.h"

class LoginResponse : public Serializable {
private:
    StatusType status;

public:
    explicit LoginResponse(const StatusType &);

    Json::Value getJson() override;

};


#endif //SERVER_LOGINRESPONSE_H
