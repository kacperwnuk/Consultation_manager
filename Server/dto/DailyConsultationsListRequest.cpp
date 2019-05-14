//
// Created by Marcin on 06.05.2019.
//

#include <iostream>
#include "DailyConsultationsListRequest.h"
#include "DailyConsultationsListResponse.h"

DailyConsultationsListRequest::DailyConsultationHelper DailyConsultationsListRequest::dailyConsultationHelper;

const b_date &DailyConsultationsListRequest::getDate() const {
    return date;
}

DailyConsultationsListRequest::DailyConsultationsListRequest(Json::Value value) :
        date(std::chrono::system_clock::now()) {
    this->date = b_date(std::chrono::milliseconds(value["consultationDateStart"].asLargestUInt()));
}

Request *DailyConsultationsListRequest::create(Json::Value value) {
    return new DailyConsultationsListRequest(value);
}

Serializable *DailyConsultationsListRequest::execute() {
    auto dao = Dao::getDaoCollection("TIN", "consultation");
    auto today = getDate();
    auto tomorrow = b_date(std::chrono::milliseconds(today.value.count() + std::chrono::milliseconds(std::chrono::hours(24)).count()));
    auto consultations = dao->getConsultationsByDate(today, tomorrow);

    return new DailyConsultationsListResponse(consultations);
}

DailyConsultationsListRequest::DailyConsultationsListRequest() : date(std::chrono::system_clock::now()) {

}
