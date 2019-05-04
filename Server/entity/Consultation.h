//
// Created by Marcin on 29.03.2019.
//

#ifndef SERVER_CONSULTATION_H
#define SERVER_CONSULTATION_H

#include <ctime>
#include <string>
#include "enums/ConsultationStatus.h"
#include "enums/ConsultationType.h"
#include "Account.h"
#include "../serialization/Serializable.h"


class Consultation : public Entity, public Serializable {
private:

    oid id;
    oid lecturerId;
    std::string room;
    oid studentId;
    ConsultationStatus consultationStatus;
    ConsultationType consultationType;
    b_date consultationDate;

public:

    Consultation(oid, std::string, oid, ConsultationStatus, ConsultationType, b_date);

    Consultation(document_view_or_value);

    Json::Value getJson() override;

    bsoncxx::document::view_or_value getDocumentFormat() override;

    oid getId() const;

    oid getLecturerId() const;

    void setLecturerId(oid lecturerId);

    const std::string &getRoom() const;

    void setRoom(const std::string &room);

    oid getStudentId() const;

    void setStudentId(oid studentId);

    ConsultationStatus getConsultationStatus() const;

    void setConsultationStatus(ConsultationStatus consultationStatus);

    ConsultationType getConsultationType() const;

    void setConsultationType(ConsultationType consultationType);

    const b_date &getConsultationDate() const;

    void setConsultationDate(const b_date &consultationDate);

    void book(Account);

    void free();
};


#endif //SERVER_CONSULTATION_H
