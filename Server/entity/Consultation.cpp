//
// Created by Marcin on 29.03.2019.
//

#include "Consultation.h"
#include "Account.h"

long long int Consultation::getId() const {
    return id;
}

void Consultation::setId(long long int id) {
    Consultation::id = id;
}

int Consultation::getLecturerId() const {
    return lecturerId;
}

void Consultation::setLecturerId(int lecturerId) {
    Consultation::lecturerId = lecturerId;
}

const std::string &Consultation::getRoom() const {
    return room;
}

void Consultation::setRoom(const std::string &room) {
    Consultation::room = room;
}

long long int Consultation::getStudentId() const {
    return studentId;
}

void Consultation::setStudentId(long long int studentId) {
    Consultation::studentId = studentId;
}

ConsultationStatus Consultation::getConsultationStatus() const {
    return consultationStatus;
}

void Consultation::setConsultationStatus(ConsultationStatus consultationStatus) {
    Consultation::consultationStatus = consultationStatus;
}

ConsultationType Consultation::getConsultationType() const {
    return consultationType;
}

void Consultation::setConsultationType(ConsultationType consultationType) {
    Consultation::consultationType = consultationType;
}

void Consultation::book(Account student) {
    Consultation::consultationStatus = STUDENT_BOOKED;
}

void Consultation::free() {
    Consultation::consultationStatus = FREE;
}
