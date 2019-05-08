//
// Created by kacper on 10.04.2019.
//

#ifndef SERVER_DAILYCONSULTATIONSLISTRESPONSE_H
#define SERVER_DAILYCONSULTATIONSLISTRESPONSE_H


#include "../entity/Consultation.h"

class DailyConsultationsListResponse : public Serializable {
private:
    std::vector<Consultation> consultations;
public:
    DailyConsultationsListResponse(std::vector<Consultation>);

    Json::Value getJson() override;
};


#endif //SERVER_DAILYCONSULTATIONSLISTRESPONSE_H
