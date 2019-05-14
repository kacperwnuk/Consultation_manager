//
// Created by kacper on 07.05.2019.
//

#ifndef SERVER_NEWCONSULTATIONREQUEST_H
#define SERVER_NEWCONSULTATIONREQUEST_H


#include <ostream>
#include "../entity/Consultation.h"
#include "../entity/ConsultationInfoForClient.h"
#include "Request.h"

class NewConsultationRequest : public Request{

    struct NewConsultationHelper{
        NewConsultationHelper(){
            Request::addToMap("NewConsultationRequest", new NewConsultationRequest());
        }
    };
    static NewConsultationHelper newConsultationHelper;

    ConsultationInfoForClient consultationInfo;

public:
    const ConsultationInfoForClient &getConsultationInfo() const;
    friend std::ostream &operator<<(std::ostream &os, const NewConsultationRequest &request);
    b_date getConsultationDateStart();
    NewConsultationRequest() = default;
    NewConsultationRequest(Json::Value);

    b_date getConsultationDateEnd();

    Request *create(Json::Value value) override;

    Serializable *execute() override;
};


#endif //SERVER_NEWCONSULTATIONREQUEST_H
