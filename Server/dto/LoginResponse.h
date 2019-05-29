//
// Created by kacper on 10.04.2019.
//

#ifndef SERVER_LOGINRESPONSE_H
#define SERVER_LOGINRESPONSE_H


#include "enums/StatusType.h"
#include "../serialization/Serializable.h"
#include "../entity/enums/AccountRole.h"

class LoginResponse : public Serializable {
private:
    StatusType status;
    AccountRole role;

public:
    explicit LoginResponse(const StatusType &);
    explicit LoginResponse(const StatusType &, const AccountRole &);

    Json::Value getJson() override;

};


#endif //SERVER_LOGINRESPONSE_H
