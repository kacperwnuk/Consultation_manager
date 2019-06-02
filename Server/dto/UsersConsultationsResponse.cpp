//
// Created by slawek on 29.05.19.
//

#include "UsersConsultationsResponse.h"

UsersConsultationsResponse::UsersConsultationsResponse(std::vector<Consultation> &consultations){
    this->consultations = consultations;
}

Json::Value UsersConsultationsResponse::getJson() {
    Json::Value value;
    if (this->consultations.empty()){
        value["consultations"];
    } else {
        for (auto consultation : consultations) {
            value["consultations"].append(consultation.getJson());
        }
    }
    value["type"] = "UsersConsultationsResponse";
    return value;
}