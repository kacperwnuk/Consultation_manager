//
// Created by Marcin on 29.03.2019.
//

#include <bsoncxx/builder/stream/document.hpp>
#include <iostream>
#include "Consultation.h"
#include "Account.h"

oid Consultation::getId() const {
    return id;
}


oid Consultation::getLecturerId() const {
    return lecturer;
}

void Consultation::setLecturerId(oid lecturerId) {
    Consultation::lecturer = lecturerId;
}

const std::string &Consultation::getRoom() const {
    return room;
}

void Consultation::setRoom(const std::string &room) {
    Consultation::room = room;
}

oid Consultation::getStudentId() const {
    return student;
}

void Consultation::setStudentId(oid studentId) {
    Consultation::student = studentId;
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


const b_date &Consultation::getConsultationDate() const {
    return consultationDate;
}

void Consultation::setConsultationDate(const b_date &consultationDate) {
    Consultation::consultationDate = consultationDate;
}

bsoncxx::document::view_or_value Consultation::getDocumentFormat() {
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value docValue = builder
            << "_id" << this->id
            << "lecturer" << this->lecturer
            << "room" << this->room
            << "student" << this->student
            << "consultationStatus" << this->consultationStatus
            << "consultationType" << this->consultationType
            << "consultationDate" << this->consultationDate
            << bsoncxx::builder::stream::finalize;
    return docValue;
}

Consultation::Consultation(oid lecturerId, std::string room, oid studentId, ConsultationStatus consultationStatus,
                           ConsultationType consultationType, b_date consultationDate) :
        lecturer(lecturerId), room(room), student(studentId), consultationStatus(consultationStatus),
        consultationType(consultationType), consultationDate(consultationDate) {

}

Consultation::Consultation(document_view_or_value document) : consultationDate(std::chrono::system_clock::now()) {
    auto stringValue = bsoncxx::to_json(document);
    Json::Reader reader;
    Json::Value jsonValue;
    reader.parse(stringValue, jsonValue);
    this->id = oid(jsonValue["_id"]["$oid"].asString());
    this->lecturer = oid(jsonValue["lecturer"]["$oid"].asString());
    this->room = jsonValue["room"].asString();
    this->student = oid(jsonValue["student"]["$oid"].asString());
    this->consultationStatus = ConsultationStatus(jsonValue["consultationStatus"].asInt());
    this->consultationType = ConsultationType(jsonValue["consultationType"].asInt());
    this->consultationDate = b_date(std::chrono::milliseconds(jsonValue["consultationDate"]["$date"].asLargestUInt()));
}

Consultation::Consultation(Json::Value jsonValue) : consultationDate(std::chrono::system_clock::now()) {

    try {
        this->id = oid(jsonValue["_id"].asString());
    } catch (std::exception &e) {

    }
    this->lecturer = oid(jsonValue["lecturer"].asString());
    this->room = jsonValue["room"].asString();
    this->student = oid(jsonValue["student"].asString());
    this->consultationStatus = ConsultationStatus(jsonValue["consultationStatus"].asInt());
    this->consultationType = ConsultationType(jsonValue["consultationType"].asInt());
    std::cout << jsonValue["consultationDate"].asString() << std::endl;
    this->consultationDate = b_date(std::chrono::milliseconds(jsonValue["consultationDate"].asLargestUInt()));
}

Json::Value Consultation::getJson() {

    Json::Value value;
    try {
        value["_id"] = this->id.to_string();
    } catch (std::exception &e) {

    }
    value["lecturer"] = this->lecturer.to_string();
    value["room"] = this->room;
    value["student"] = this->student.to_string();
    value["consultationStatus"] = this->consultationStatus;
    value["consultationType"] = this->consultationType;
    value["consultationDate"] = static_cast<unsigned long long>(this->consultationDate.value.count());

    return value;
}

std::ostream &operator<<(std::ostream &os, const Consultation &consultation) {
    os << " id: "
       << consultation.id.to_string() << " lecturer: " << consultation.lecturer.to_string() << " room: "
       << consultation.room
       << " student: " << consultation.student.to_string() << " consultationStatus: "
       << consultation.consultationStatus
       << " consultationType: " << consultation.consultationType << " consultationDate: "
       << consultation.consultationDate;
    return os;
}


