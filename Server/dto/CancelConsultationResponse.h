//
// Created by slawek on 29.05.19.
//

#ifndef SERVER_CANCELCONSULTATIONRESPONSE_H
#define SERVER_CANCELCONSULTATIONRESPONSE_H


#include "../serialization/Serializable.h"
#include "enums/StatusType.h"

class CancelConsultationResponse : public Serializable{
    StatusType status;
public:
    explicit CancelConsultationResponse(StatusType);

    Json::Value getJson() override;

};


#endif //SERVER_CANCELCONSULTATIONRESPONSE_H
