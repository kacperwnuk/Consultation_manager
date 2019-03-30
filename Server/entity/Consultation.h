//
// Created by Marcin on 29.03.2019.
//

#ifndef SERVER_CONSULTATION_H
#define SERVER_CONSULTATION_H

#include <string>
#include "enums/ConsultationStatus.h"
#include "enums/ConsultationType.h"
#include "Account.h"

class Consultation {
private:
    long long id;
public:
    long long int getId() const;

    void setId(long long int id);

    int getLecturerId() const;

    void setLecturerId(int lecturerId);

    const std::string &getRoom() const;

    void setRoom(const std::string &room);

    long long int getStudentId() const;

    void setStudentId(long long int studentId);

    ConsultationStatus getConsultationStatus() const;

    void setConsultationStatus(ConsultationStatus consultationStatus);

    ConsultationType getConsultationType() const;

    void setConsultationType(ConsultationType consultationType);

    void book(Account);

    void free();

private:
    int lecturerId;

    std::string room;
    long long studentId;
    ConsultationStatus consultationStatus;
    ConsultationType consultationType;
};


#endif //SERVER_CONSULTATION_H
