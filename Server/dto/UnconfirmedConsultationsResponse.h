//
// Created by slawek on 01.06.19.
//

#ifndef SERVER_UNCONFIRMEDCONSULTATIONSRESPONSE_H
#define SERVER_UNCONFIRMEDCONSULTATIONSRESPONSE_H


#include "../serialization/Serializable.h"
#include "../entity/ConsultationInfoForClient.h"

class UnconfirmedConsultationsResponse : public Serializable {
    private:
    std::vector<ConsultationInfoForClient> consultations;
    public:
    UnconfirmedConsultationsResponse(std::vector<ConsultationInfoForClient>);

    Json::Value getJson() override;
};


#endif //SERVER_UNCONFIRMEDCONSULTATIONSRESPONSE_H
