//
// Created by kacper on 09.05.2019.
//

#include "ConsultationInfoForClient.h"

Json::Value ConsultationInfoForClient::getJson() {
    Json::Value value;
    value["lecturer"] = this->lecturer.getJson();
    value["student"] = this->student.getJson();
    value["consultationDateStart"] = static_cast<unsigned long long>(this->consultationDateStart.value.count());
    value["consultationDateEnd"] = static_cast<unsigned long long>(this->consultationDateEnd.value.count());
    value["room"] = this->room;
    value["consultationType"] = this->consultationType;
    return value;
}

ConsultationInfoForClient::ConsultationInfoForClient(std::string id, const AccountInfoForClient& consultationCreator,
                                                     const b_date &consultationDateStart,
                                                     const b_date &consultationDateEnd, const std::string &room,
                                                     ConsultationType consultationType) : id(id), consultationDateStart(consultationDateStart), consultationDateEnd(consultationDateEnd),
                                                                                          room(room), consultationType(
                consultationType) {
    if (this->consultationType == ConsultationType::LECTURER_SUGGESTED){
        this->lecturer = consultationCreator;
    } else {
        this->student = consultationCreator;
    }

}


std::ostream &operator<<(std::ostream &os, const ConsultationInfoForClient &client) {
    os << " id: " << client.id.to_string() << " lecturer: "
       << client.lecturer << " consultationDateStart: " << client.consultationDateStart
       << " consultationDateEnd: " << client.consultationDateEnd << " room: " << client.room << " consultationType: "
       << client.consultationType;
    return os;
}

const oid &ConsultationInfoForClient::getId() const {
    return id;
}


const b_date &ConsultationInfoForClient::getConsultationDateStart() const {
    return consultationDateStart;
}

const b_date &ConsultationInfoForClient::getConsultationDateEnd() const {
    return consultationDateEnd;
}

const std::string &ConsultationInfoForClient::getRoom() const {
    return room;
}

ConsultationType ConsultationInfoForClient::getConsultationType() const {
    return consultationType;
}

ConsultationInfoForClient::ConsultationInfoForClient() : consultationDateStart(std::chrono::system_clock::now()), consultationDateEnd(std::chrono::system_clock::now()) {

}

const AccountInfoForClient &ConsultationInfoForClient::getLecturer() const {
    return lecturer;
}

const AccountInfoForClient &ConsultationInfoForClient::getStudent() const {
    return student;
}
