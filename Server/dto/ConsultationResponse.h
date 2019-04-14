//
// Created by kacper on 10.04.2019.
//

#ifndef SERVER_CONSULTATIONRESPONSE_H
#define SERVER_CONSULTATIONRESPONSE_H


#include "../entity/Consultation.h"

class ConsultationResponse: public Serializable {
private:
    std::vector<Consultation> consultations;
public:
    ConsultationResponse(std::vector<Consultation>);
    Json::Value getJson() override;
};


#endif //SERVER_CONSULTATIONRESPONSE_H
