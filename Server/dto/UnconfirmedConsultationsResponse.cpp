//
// Created by slawek on 01.06.19.
//

#include "UnconfirmedConsultationsResponse.h"

UnconfirmedConsultationsResponse::UnconfirmedConsultationsResponse(std::vector<ConsultationInfoForClient> consultations) :
        consultations(std::move(consultations)) {

}

Json::Value UnconfirmedConsultationsResponse::getJson() {
    Json::Value value;
    if (this->consultations.empty()){
        value["consultations"];
    } else {
        for (auto consultation : consultations) {
            value["consultations"].append(consultation.getJson());
        }
    }

    value["type"] = "DailyConsultationListResponse";
    return value;
}