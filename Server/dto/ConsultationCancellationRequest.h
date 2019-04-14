//
// Created by kacper on 10.04.2019.
//

#ifndef SERVER_CONSULTATIONCANCELLATIONREQUEST_H
#define SERVER_CONSULTATIONCANCELLATIONREQUEST_H


#include "../entity/Entity.h"
#include "../serialization/Serializable.h"

class ConsultationCancellationRequest {
    oid consultationId;

public:
    ConsultationCancellationRequest(Json::Value);

    const oid &getConsultationId() const;

};


#endif //SERVER_CONSULTATIONCANCELLATIONREQUEST_H


