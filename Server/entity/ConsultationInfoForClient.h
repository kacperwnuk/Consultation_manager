//
// Created by kacper on 09.05.2019.
//

#ifndef SERVER_CONSULTATIONINFOFORCLIENT_H
#define SERVER_CONSULTATIONINFOFORCLIENT_H


#include <ostream>
#include "Account.h"
#include "enums/ConsultationType.h"
#include "AccountInfoForClient.h"

class ConsultationInfoForClient: Serializable {

    oid id;
    AccountInfoForClient consultationCreator;
    b_date consultationDateStart;
    b_date consultationDateEnd;
    std::string room;
    ConsultationType consultationType;

public:

    ConsultationInfoForClient(std::string, const AccountInfoForClient &consultationCreator, const b_date &consultationDateStart,
                              const b_date &consultationDateEnd, const std::string &room,
                              ConsultationType consultationType);
    ConsultationInfoForClient();
    ConsultationInfoForClient(Json::Value);

    Json::Value getJson() override;

    friend std::ostream &operator<<(std::ostream &os, const ConsultationInfoForClient &client);

    const oid &getId() const;

    const AccountInfoForClient &getConsultationCreator() const;

    const b_date &getConsultationDateStart() const;

    const b_date &getConsultationDateEnd() const;

    const std::string &getRoom() const;

    ConsultationType getConsultationType() const;


};


#endif //SERVER_CONSULTATIONINFOFORCLIENT_H
