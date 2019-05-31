//
// Created by slawek on 31.05.19.
//

#ifndef SERVER_REJECTCONSULTATIONRESPONSE_H
#define SERVER_REJECTCONSULTATIONRESPONSE_H


#include "../serialization/Serializable.h"
#include "enums/StatusType.h"

class RejectConsultationResponse : public Serializable{
    StatusType status;
public:
    explicit RejectConsultationResponse(StatusType);

    Json::Value getJson() override;
};


#endif //SERVER_REJECTCONSULTATIONRESPONSE_H
