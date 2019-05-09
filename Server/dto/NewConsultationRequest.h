//
// Created by kacper on 07.05.2019.
//

#ifndef SERVER_NEWCONSULTATIONREQUEST_H
#define SERVER_NEWCONSULTATIONREQUEST_H


#include <ostream>
#include "../entity/Consultation.h"
#include "../entity/ConsultationInfoForClient.h"

class NewConsultationRequest {
private:
    ConsultationInfoForClient consultationInfo;
public:
    const ConsultationInfoForClient &getConsultationInfo() const;

public:
    friend std::ostream &operator<<(std::ostream &os, const NewConsultationRequest &request);
    b_date getConsultationDateStart();
    NewConsultationRequest(Json::Value);

    b_date getConsultationDateEnd();
};


#endif //SERVER_NEWCONSULTATIONREQUEST_H
