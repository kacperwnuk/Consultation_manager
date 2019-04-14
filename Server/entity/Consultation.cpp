//
// Created by Marcin on 29.03.2019.
//

#include <bsoncxx/builder/stream/document.hpp>
#include "Consultation.h"
#include "Account.h"

oid Consultation::getId() const {
    return id;
}


oid Consultation::getLecturerId() const {
    return lecturerId;
}

void Consultation::setLecturerId(oid lecturerId) {
    Consultation::lecturerId = lecturerId;
}

const std::string &Consultation::getRoom() const {
    return room;
}

void Consultation::setRoom(const std::string &room) {
    Consultation::room = room;
}

oid Consultation::getStudentId() const {
    return studentId;
}

void Consultation::setStudentId(oid studentId) {
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
            << "lecturerId" << this->lecturerId
            << "room" << this->room
            << "studentId" << this->studentId
            << "consultationStatus" << this->consultationStatus
            << "consultationType" << this->consultationType
            << "consultationDate" << this->consultationDate
            << bsoncxx::builder::stream::finalize;
    return docValue;
}

Consultation::Consultation(oid lecturerId, std::string room, oid studentId, ConsultationStatus consultationStatus,
                           ConsultationType consultationType, b_date consultationDate) :
        lecturerId(lecturerId), room(room), studentId(studentId), consultationStatus(consultationStatus),
        consultationType(consultationType), consultationDate(consultationDate) {

}

Consultation::Consultation(document_view_or_value document) : consultationDate(std::chrono::system_clock::now()) {
    auto stringValue = bsoncxx::to_json(document);
    Json::Reader reader;
    Json::Value jsonValue;
    reader.parse(stringValue, jsonValue);
    this->id = oid(jsonValue["_id"]["$oid"].asString());
    this->lecturerId = oid(jsonValue["lecturerId"]["$oid"].asString());
    this->room = jsonValue["room"].asString();
    this->studentId = oid(jsonValue["studentId"]["$oid"].asString());
    this->consultationStatus = ConsultationStatus(jsonValue["consultationStatus"].asInt());
    this->consultationType = ConsultationType(jsonValue["consultationType"].asInt());
    this->consultationDate = b_date(std::chrono::milliseconds(jsonValue["consultationDate"]["$date"].asLargestUInt()));
}

Json::Value Consultation::getJson() {

    Json::Value value;
    value["_id"] = this->id.to_string();
    value["lecturerId"] = this->lecturerId.to_string();
    value["room"] = this->room;
    value["studentId"] = this->studentId.to_string();
    value["consultationStatus"] = this->consultationStatus;
    value["consultationType"] = this->consultationType;
    value["consultationDate"] = static_cast<unsigned long long>(this->consultationDate.value.count());

    return value;
}


