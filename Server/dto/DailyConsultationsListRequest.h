//
// Created by Marcin on 06.05.2019.
//

#ifndef SERVER_DAILYCONSULTATIONLISTREQUEST_H
#define SERVER_DAILYCONSULTATIONLISTREQUEST_H

#include <string>
#include <jsoncpp/json/value.h>
#include <ostream>
#include "../entity/Entity.h"

class DailyConsultationsListRequest {
private:
    b_date date;
public:
    const b_date &getDate() const;

    DailyConsultationsListRequest(Json::Value);
};


#endif //SERVER_DAILYCONSULTATIONLISTREQUEST_H
