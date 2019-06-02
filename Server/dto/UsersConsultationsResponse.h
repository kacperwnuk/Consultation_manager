//
// Created by slawek on 29.05.19.
//

#ifndef SERVER_USERSCONSULTATIONSRESPONSE_H
#define SERVER_USERSCONSULTATIONSRESPONSE_H


#include "../serialization/Serializable.h"
#include "../entity/ConsultationInfoForClient.h"
#include "../entity/Consultation.h"

class UsersConsultationsResponse : public Serializable{

    std::vector<Consultation> consultations;
public:
    UsersConsultationsResponse(std::vector<Consultation> &consultations);
    Json::Value getJson() override;
};


#endif //SERVER_USERSCONSULTATIONSRESPONSE_H
