//
// Created by root on 5/28/19.
//

#include "ReservationRequest.h"
#include "ReservationResponse.h"

ReservationRequest::ReservationHelper ReservationRequest::helper;


ReservationRequest::ReservationRequest(Json::Value value) {
    this->login = value["login"].asString();
    this->id = value["id"].asString();

}


const std::string &ReservationRequest::getId() const {
    return id;
}

void ReservationRequest::setId(const std::string &id) {
    ReservationRequest::id = id;
}

const std::string &ReservationRequest::getLogin() const {
    return login;
}

void ReservationRequest::setLogin(const std::string &login) {
    ReservationRequest::login = login;
}


std::unique_ptr<Request> ReservationRequest::create(Json::Value value) {
    std::unique_ptr<Request> request (new ReservationRequest(value));
    return std::move(request);
}


std::unique_ptr<Serializable> ReservationRequest::execute() {
    auto dao = Dao::getDaoCollection("TIN", "consultation");
    auto dao2 = Dao::getDaoCollection("TIN", "account");
    try {
        auto oldConsultation = dao->getConsultationById(this->getId());
        /*
        if (oldConsultation.getStatus() != FREE) {
            std::cout << "konsultacja nie jest wolna:" << oldConsultation.getStatus() <<  std::endl;
            std::unique_ptr<Serializable> response(new ReservationResponse(ERROR));
            return std::move(response);
        } */

        auto account = dao2->getAccountByLogin(getLogin());

        AccountInfoForClient info(account.getName(), account.getSurname(), account.getLogin());

        Consultation newConsultation(oldConsultation.getLecturer(), oldConsultation.getRoom(), info, STUDENT_BOOKED,
                                     oldConsultation.getType(), oldConsultation.getConsultationDateStart(),
                                     oldConsultation.getConsultationDateEnd());

        newConsultation.setID(oldConsultation.getId().to_string());

        dao->updateDocument(oldConsultation.getDocumentFormat(), newConsultation.getDocumentFormat());
    } catch (std::exception &e) {
        std::cout << e.what();
        std::unique_ptr<Serializable> response(new ReservationResponse(ERROR));
        return std::move(response);
    }

    std::cout << "Reserwacja pomyślna" << std::endl;
    std::unique_ptr<Serializable> response(new ReservationResponse(OK));
    return std::move(response);


    }

