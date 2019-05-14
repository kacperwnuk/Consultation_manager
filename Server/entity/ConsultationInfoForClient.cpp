//
// Created by kacper on 09.05.2019.
//

#include "ConsultationInfoForClient.h"

Json::Value ConsultationInfoForClient::getJson() {
    Json::Value value;
    value["consultationCreator"] = this->consultationCreator.getJson();
    value["consultationDateStart"] = static_cast<unsigned long long>(this->consultationDateStart.value.count());
    value["consultationDateEnd"] = static_cast<unsigned long long>(this->consultationDateEnd.value.count());
    value["room"] = this->room;
    value["consultationType"] = this->consultationType;
    return Json::Value();
}

ConsultationInfoForClient::ConsultationInfoForClient(std::string id, const AccountInfoForClient &consultationCreator,
                                                     const b_date &consultationDateStart,
                                                     const b_date &consultationDateEnd, const std::string &room,
                                                     ConsultationType consultationType) : id(id), consultationCreator(
        consultationCreator), consultationDateStart(consultationDateStart), consultationDateEnd(consultationDateEnd),
                                                                                          room(room), consultationType(
                consultationType) {}

ConsultationInfoForClient::ConsultationInfoForClient(Json::Value jsonValue) : consultationDateStart(
        std::chrono::system_clock::now()), consultationDateEnd(std::chrono::system_clock::now()) {

    try{
        this->id = oid(jsonValue["_id"].asString());
    }catch(std::exception &e){
        e.what();
    }
    this->consultationType = ConsultationType(jsonValue["consultationType"].asInt());
    this->room = jsonValue["room"].asString();
    this->consultationDateStart = b_date(std::chrono::milliseconds(jsonValue["consultationDateStart"].asLargestUInt()));
    this->consultationDateEnd = b_date(std::chrono::milliseconds(jsonValue["consultationDateEnd"].asLargestUInt()));
    this->consultationCreator = AccountInfoForClient(jsonValue["consultationCreator"]);
}

std::ostream &operator<<(std::ostream &os, const ConsultationInfoForClient &client) {
    os << " id: " << client.id.to_string() << " consultationCreator: "
       << client.consultationCreator << " consultationDateStart: " << client.consultationDateStart
       << " consultationDateEnd: " << client.consultationDateEnd << " room: " << client.room << " consultationType: "
       << client.consultationType;
    return os;
}

const oid &ConsultationInfoForClient::getId() const {
    return id;
}

const AccountInfoForClient &ConsultationInfoForClient::getConsultationCreator() const {
    return consultationCreator;
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
