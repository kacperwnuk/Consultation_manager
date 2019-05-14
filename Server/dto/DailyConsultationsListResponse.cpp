//
// Created by kacper on 10.04.2019.
//

#include "DailyConsultationsListResponse.h"

DailyConsultationsListResponse::DailyConsultationsListResponse(std::vector<Consultation> consultations) :
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

    value["type"] = "DailyConsultationListResponse";
    return value;
}
