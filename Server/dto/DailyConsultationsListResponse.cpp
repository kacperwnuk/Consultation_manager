//
// Created by kacper on 10.04.2019.
//

#include "DailyConsultationsListResponse.h"
#include "enums/ResponseType.h"

DailyConsultationsListResponse::DailyConsultationsListResponse(std::vector<Consultation> consultations) :
        consultations(std::move(consultations)) {

}

Json::Value DailyConsultationsListResponse::getJson() {
    Json::Value value;
    for (auto consultation : consultations) {
        value["consultations"].append(consultation.getJson());
    }
    value["type"] = ResponseType::DailyConsultationsListResp;
    return value;
}
