//
// Created by root on 6/3/19.
//

#ifndef SERVER_KEYCONFIRMATIONRESPONSE_H
#define SERVER_KEYCONFIRMATIONRESPONSE_H


#include "../serialization/Serializable.h"
#include "enums/StatusType.h"

class KeyConfirmationResponse : public Serializable {
    StatusType status;
public:
    explicit KeyConfirmationResponse(StatusType);

    Json::Value getJson() override;

};


#endif //SERVER_KEYCONFIRMATIONRESPONSE_H
