//
// Created by Marcin on 06.05.2019.
//

#ifndef SERVER_DAILYCONSULTATIONLISTREQUEST_H
#define SERVER_DAILYCONSULTATIONLISTREQUEST_H

#include <string>
#include <jsoncpp/json/value.h>
#include <ostream>
#include "../entity/Entity.h"
#include "Request.h"

class DailyConsultationsListRequest : public Request {

    struct DailyConsultationHelper {
        DailyConsultationHelper() {
            std::cout << "Dodaje DailyConsList" << std::endl;
            Request::addToMap("DailyConsultationsListRequest", std::make_unique<DailyConsultationsListRequest>());
        }
    };

    static DailyConsultationHelper dailyConsultationHelper;

    b_date date;
public:
    const b_date &getDate() const;

    DailyConsultationsListRequest();

    DailyConsultationsListRequest(Json::Value);

    ~DailyConsultationsListRequest() override {
        std::cout << "Zamykam Daily" << std::endl;
    }

    std::unique_ptr<Request> create(Json::Value) override;

    std::unique_ptr<Serializable> execute() override;
};


#endif //SERVER_DAILYCONSULTATIONLISTREQUEST_H
