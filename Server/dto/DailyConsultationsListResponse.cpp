//
// Created by kacper on 10.04.2019.
//

#include "DailyConsultationsListResponse.h"
#include "enums/ResponseType.h"

DailyConsultationsListResponse::DailyConsultationsListResponse(std::vector<ConsultationInfoForClient> consultations) :
        consultations(std::move(consultations)) {

}

Json::Value DailyConsultationsListResponse::getJson() {
    Json::Value value;
    if (this->consultations.empty()){
        value["consultations"];
    } else {
        for (auto consultation : consultations) {
            value["consultations"].append(consultation.getJson());
        }
    }

    value["type"] = ResponseType::DailyConsultationsListResp;
    return value;
}
