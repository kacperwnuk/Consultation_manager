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

const std::string &Consultation::getRoom() const {
    return room;
}

void Consultation::setRoom(const std::string &room) {
    Consultation::room = room;
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


const b_date &Consultation::getConsultationDateStart() const {
    return consultationDateStart;
}

void Consultation::setConsultationDateStart(const b_date &consultationDate) {
    Consultation::consultationDateStart = consultationDate;
}

bsoncxx::document::view_or_value Consultation::getDocumentFormat() {
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value docValue = builder
            << "_id" << this->id
            << "lecturer" << this->lecturer.getDocumentFormat()
            << "room" << this->room
            << "student" << this->student.getDocumentFormat()
            << "consultationStatus" << this->consultationStatus
            << "consultationType" << this->consultationType
            << "consultationDateStart" << this->consultationDateStart
            << "consultationDateEnd" << this->consultationDateEnd
            << bsoncxx::builder::stream::finalize;
    return docValue;
}

Consultation::Consultation(AccountInfoForClient lecturer, std::string room, AccountInfoForClient student,
                           ConsultationStatus consultationStatus,
                           ConsultationType consultationType, b_date consultationDateStart, b_date consultatinDateEnd) :
        lecturer(lecturer), room(room), student(student), consultationStatus(consultationStatus),
        consultationType(consultationType), consultationDateStart(consultationDateStart),
        consultationDateEnd(consultatinDateEnd) {

}

Consultation::Consultation(document_view_or_value document) : consultationDateStart(std::chrono::system_clock::now()),
                                                              consultationDateEnd(std::chrono::system_clock::now()) {
    auto stringValue = bsoncxx::to_json(document);
    Json::Reader reader;
    Json::Value jsonValue;
    reader.parse(stringValue, jsonValue);
    this->id = oid(jsonValue["_id"]["$oid"].asString());
    this->lecturer = AccountInfoForClient(jsonValue["lecturer"]);
    this->room = jsonValue["room"].asString();
    this->student = AccountInfoForClient(jsonValue["student"]);
    this->consultationStatus = ConsultationStatus(jsonValue["consultationStatus"].asInt());
    this->consultationType = ConsultationType(jsonValue["consultationType"].asInt());
    this->consultationDateStart = b_date(
            std::chrono::milliseconds(jsonValue["consultationDateStart"]["$date"].asLargestUInt()));
    this->consultationDateEnd = b_date(
            std::chrono::milliseconds(jsonValue["consultationDateEnd"]["$date"].asLargestUInt()));
}

Consultation::Consultation(Json::Value jsonValue) : consultationDateStart(std::chrono::system_clock::now()),
                                                    consultationDateEnd(std::chrono::system_clock::now()) {

    try {
        this->id = oid(jsonValue["_id"].asString());
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    this->lecturer = AccountInfoForClient(jsonValue["lecturer"]);
    this->room = jsonValue["room"].asString();
    this->student = AccountInfoForClient(jsonValue["student"]);
    this->consultationStatus = ConsultationStatus(jsonValue["consultationStatus"].asInt());
    this->consultationType = ConsultationType(jsonValue["consultationType"].asInt());
    std::cout << jsonValue["consultationDateStart"].asString() << std::endl;
    this->consultationDateStart = b_date(std::chrono::milliseconds(jsonValue["consultationDateStart"].asLargestUInt()));
    this->consultationDateEnd = b_date(std::chrono::milliseconds(jsonValue["consultationDateEnd"].asLargestUInt()));
}

Json::Value Consultation::getJson() {

    Json::Value value;
    try {
        value["_id"] = this->id.to_string();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    value["lecturer"] = this->lecturer.getJson();
    value["room"] = this->room;
    value["student"] = this->student.getJson();
    value["consultationStatus"] = this->consultationStatus;
    value["consultationType"] = this->consultationType;
    value["consultationDateStart"] = static_cast<unsigned long long>(this->consultationDateStart.value.count());
    value["consultationDateEnd"] = static_cast<unsigned long long>(this->consultationDateEnd.value.count());

    return value;
}

std::ostream &operator<<(std::ostream &os, const Consultation &consultation) {
    os << " id: "
       << consultation.id.to_string() << " lecturer: " << consultation.lecturer << " room: "
       << consultation.room
       << " student: " << consultation.student << " consultationStatus: "
       << consultation.consultationStatus
       << " consultationType: " << consultation.consultationType << " consultationDateStart: "
       << consultation.consultationDateStart << "consultationDateEnd" << consultation.consultationDateEnd;
    return os;
}

Consultation::Consultation(ConsultationInfoForClient consultationClientInfo, ConsultationStatus status)
        : consultationStatus(status), id(consultationClientInfo.getId()),
          lecturer(consultationClientInfo.getConsultationCreator()), room(consultationClientInfo.getRoom()), student(),
          consultationType(consultationClientInfo.getConsultationType()),
          consultationDateStart(consultationClientInfo.getConsultationDateStart()),
          consultationDateEnd(consultationClientInfo.getConsultationDateEnd()) {

}

const AccountInfoForClient &Consultation::getLecturer() const {
    return lecturer;
}

const b_date &Consultation::getConsultationDateEnd() const {
    return consultationDateEnd;
}


