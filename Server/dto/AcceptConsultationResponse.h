//
// Created by slawek on 31.05.19.
//

#ifndef SERVER_ACCEPTCONSULTATIONRESPONSE_H
#define SERVER_ACCEPTCONSULTATIONRESPONSE_H


#include "../serialization/Serializable.h"
#include "enums/StatusType.h"

class AcceptConsultationResponse : public Serializable{
    StatusType status;
public:
    explicit AcceptConsultationResponse(StatusType);

    Json::Value getJson() override;
};


#endif //SERVER_ACCEPTCONSULTATIONRESPONSE_H
