//
// Created by kacper on 09.05.2019.
//

#ifndef SERVER_CONSULTATIONINFOFORCLIENT_H
#define SERVER_CONSULTATIONINFOFORCLIENT_H


#include <ostream>
#include "Account.h"
#include "enums/ConsultationType.h"
#include "AccountInfoForClient.h"
#include "enums/ConsultationStatus.h"

class ConsultationInfoForClient: Serializable {

    oid id;
    AccountInfoForClient lecturer;
    b_date consultationDateStart;
    b_date consultationDateEnd;
    AccountInfoForClient student;
    std::string room;
    ConsultationType consultationType;

public:
    const AccountInfoForClient &getLecturer() const;

    const AccountInfoForClient &getStudent() const;

    ConsultationInfoForClient(std::string, const AccountInfoForClient& lecturer, const AccountInfoForClient& student, const b_date &consultationDateStart,
                              const b_date &consultationDateEnd, const std::string &room,
                              ConsultationType consultationType);
    ConsultationInfoForClient();

    Json::Value getJson() override;

    friend std::ostream &operator<<(std::ostream &os, const ConsultationInfoForClient &client);

    const oid &getId() const;

    const b_date &getConsultationDateStart() const;

    const b_date &getConsultationDateEnd() const;

    const std::string &getRoom() const;

    ConsultationType getConsultationType() const;


};


#endif //SERVER_CONSULTATIONINFOFORCLIENT_H
