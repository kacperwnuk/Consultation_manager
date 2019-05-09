//
// Created by kacper on 07.05.2019.
//

#ifndef SERVER_NEWCONSULTATIONRESPONSE_H
#define SERVER_NEWCONSULTATIONRESPONSE_H


#include "../serialization/Serializable.h"
#include "enums/StatusType.h"

class NewConsultationResponse: public Serializable {
private:
    StatusType statusType;
public:
    NewConsultationResponse(StatusType);

    Json::Value getJson() override;

};


#endif //SERVER_NEWCONSULTATIONRESPONSE_H
