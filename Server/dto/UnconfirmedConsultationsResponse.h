//
// Created by slawek on 01.06.19.
//

#ifndef SERVER_UNCONFIRMEDCONSULTATIONSRESPONSE_H
#define SERVER_UNCONFIRMEDCONSULTATIONSRESPONSE_H


#include "../serialization/Serializable.h"
#include "../entity/ConsultationInfoForClient.h"
#include "../entity/Consultation.h"

class UnconfirmedConsultationsResponse : public Serializable {
    private:
    std::vector<Consultation> consultations;
    public:
    UnconfirmedConsultationsResponse(std::vector<Consultation>);

    Json::Value getJson() override;
};


#endif //SERVER_UNCONFIRMEDCONSULTATIONSRESPONSE_H
