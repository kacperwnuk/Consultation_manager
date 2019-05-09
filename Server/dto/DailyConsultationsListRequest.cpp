//
// Created by Marcin on 06.05.2019.
//

#include "DailyConsultationsListRequest.h"

const b_date &DailyConsultationsListRequest::getDate() const {
    return date;
}

DailyConsultationsListRequest::DailyConsultationsListRequest(Json::Value value) :
        date(std::chrono::system_clock::now()) {
    this->date = b_date(std::chrono::milliseconds(value["consultationDateStart"].asLargestUInt()));
}