//
// Created by Marcin on 29.03.2019.
//

#ifndef SERVER_CONSULTATION_H
#define SERVER_CONSULTATION_H

#include <ctime>
#include <string>
#include <ostream>
#include "enums/ConsultationStatus.h"
#include "enums/ConsultationType.h"
#include "Account.h"
#include "../serialization/Serializable.h"
#include "AccountInfoForClient.h"
#include "ConsultationInfoForClient.h"


class Consultation : public Entity, public Serializable {
private:

    oid id;
    AccountInfoForClient lecturer;
    std::string room;
    AccountInfoForClient student;
    ConsultationStatus consultationStatus;
    ConsultationType consultationType;
    b_date consultationDateStart;
    b_date consultationDateEnd;

public:

    Consultation(AccountInfoForClient, std::string, AccountInfoForClient, ConsultationStatus, ConsultationType, b_date, b_date);

    Consultation(document_view_or_value);
    Consultation(Json::Value);
    Consultation();
    Consultation(ConsultationInfoForClient consultationClientInfo, ConsultationStatus status);

    Json::Value getJson() override;

    bsoncxx::document::view_or_value getDocumentFormat() override;

    oid getId() const;

    void setID(std::string toid) {
        oid newID(toid);
        this->id = newID;
    }

    const std::string &getRoom() const;

    const ConsultationStatus getStatus() {return consultationStatus;}

    const ConsultationType  getType() { return consultationType; }

    void setStatus(ConsultationStatus newStatus) {consultationStatus = newStatus;}

    void setRoom(const std::string &room);

    ConsultationStatus getConsultationStatus() const;

    void setConsultationStatus(ConsultationStatus consultationStatus);

    ConsultationType getConsultationType() const;

    const AccountInfoForClient &getLecturer() const;

    const AccountInfoForClient &getStudent() const;

    const b_date &getConsultationDateEnd() const;

    void setConsultationType(ConsultationType consultationType);

    const b_date &getConsultationDateStart() const;

    void setConsultationDateStart(const b_date &consultationDate);

    void book(Account);

    void free();

    friend std::ostream &operator<<(std::ostream &os, const Consultation &consultation);
};


#endif //SERVER_CONSULTATION_H
