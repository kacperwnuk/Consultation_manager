//
// Created by kacper on 10.04.2019.
//

#include "ConsultationResponse.h"

ConsultationResponse::ConsultationResponse(std::vector<Consultation> consultations) :
        consultations(std::move(consultations)) {

}

Json::Value ConsultationResponse::getJson() {
    Json::Value value;
    for (auto consultation : consultations) {
        value["consultations"].append(consultation.getJson());
    }

    return value;
}
