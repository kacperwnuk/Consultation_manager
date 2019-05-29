//
// Created by root on 5/28/19.
//

#ifndef SERVER_RESERVATIONREQUEST_H
#define SERVER_RESERVATIONREQUEST_H

#include "../entity/Consultation.h"
#include "Request.h"


class ReservationRequest: public Request {

    struct ReservationHelper {
        ReservationHelper() {
            std::cout << "Dodaje Reservation" << std::endl;
            Request::addToMap("ConsultationReservationRequest", std::make_unique<ReservationRequest>());
        }
    };

private:
    std::string login;
    std::string id;
    static ReservationHelper helper;

public:
    const std::string &getId() const;

    void setId(const std::string &id);

    const std::string &getLogin() const;

    void setLogin(const std::string &login);

    ReservationRequest() = default;

    explicit ReservationRequest(Json::Value);

    ~ReservationRequest() override {
        std::cout << "Zamykam registration" << std::endl;
    }

    std::unique_ptr<Request> create(Json::Value) override;

    std::unique_ptr<Serializable> execute(Context&) override;

};


#endif //SERVER_RESERVATIONREQUEST_H
