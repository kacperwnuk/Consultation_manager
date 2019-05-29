//
// Created by slawek on 29.05.19.
//

#ifndef SERVER_ACCEPTACCOUNTSRESPONSE_H
#define SERVER_ACCEPTACCOUNTSRESPONSE_H


#include "../serialization/Serializable.h"
#include "enums/StatusType.h"

class AcceptAccountsResponse : public Serializable{
    StatusType status;
public:
    explicit AcceptAccountsResponse(StatusType);

    Json::Value getJson() override;

};


#endif //SERVER_ACCEPTACCOUNTSRESPONSE_H
