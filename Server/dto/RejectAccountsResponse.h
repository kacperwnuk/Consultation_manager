//
// Created by slawek on 31.05.19.
//

#ifndef SERVER_REJECTACCOUNTSRESPONSE_H
#define SERVER_REJECTACCOUNTSRESPONSE_H


#include "../serialization/Serializable.h"
#include "enums/StatusType.h"

class RejectAccountsResponse : public Serializable{
    StatusType status;
public:
    explicit RejectAccountsResponse(StatusType);

    Json::Value getJson() override;

};


#endif //SERVER_REJECTACCOUNTSRESPONSE_H
