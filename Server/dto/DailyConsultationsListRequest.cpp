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

std::unique_ptr<Request> DailyConsultationsListRequest::create(Json::Value value) {
    std::unique_ptr<Request> request (new DailyConsultationsListRequest(value));
    return std::move(request);
}

std::unique_ptr<Serializable> DailyConsultationsListRequest::execute(Context& context) {

    if (!context.isLogged()){
        std::unique_ptr<Serializable> response (new DailyConsultationsListResponse(std::vector<Consultation>()));
        return std::move(response);
    }

    auto dao = Dao::getDaoCollection("TIN", "consultation");
    auto today = getDate();
    auto tomorrow = b_date(std::chrono::milliseconds(today.value.count() + std::chrono::milliseconds(std::chrono::hours(24)).count()));

    try {
        auto consultations = dao->getConsultationsByDate(today, tomorrow);
        std::unique_ptr<Serializable> response(new DailyConsultationsListResponse(consultations));
        return std::move(response);
    } catch (std::exception &e) {
        std::cout << e.what();
        std::unique_ptr<Serializable> response (new DailyConsultationsListResponse(std::vector<Consultation>()));
        return std::move(response);
    }


}

DailyConsultationsListRequest::DailyConsultationsListRequest() : date(std::chrono::system_clock::now()) {

}
