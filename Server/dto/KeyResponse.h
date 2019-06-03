//
// Created by root on 6/3/19.
//

#ifndef SERVER_KEYRESPONSE_H
#define SERVER_KEYRESPONSE_H


#include "../serialization/Serializable.h"
#include "enums/StatusType.h"

class KeyResponse: public Serializable {
    StatusType status;
    std::string newKey;
public:
    explicit KeyResponse(StatusType, std::string);

    Json::Value getJson() override;

};


#endif //SERVER_KEYRESPONSE_H
