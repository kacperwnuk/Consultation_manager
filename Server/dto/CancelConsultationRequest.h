//
// Created by slawek on 29.05.19.
//

#ifndef SERVER_CANCELCONSULTATIONREQUEST_H
#define SERVER_CANCELCONSULTATIONREQUEST_H


#include "Request.h"

class CancelConsultationRequest  : public Request {

    struct CancelConsultationHelper {
        CancelConsultationHelper() {
            std::cout << "Dodaje Reservation" << std::endl;
            Request::addToMap("CancelConsultationRequest", std::make_unique<CancelConsultationRequest>());
        }
    };

private:
    std::string login;
    std::string id;
    static CancelConsultationHelper helper;

public:
    const std::string &getId() const;

    void setId(const std::string &id);

    const std::string &getLogin() const;

    void setLogin(const std::string &login);

    CancelConsultationRequest() = default;

    explicit CancelConsultationRequest(Json::Value);

    ~CancelConsultationRequest() override {
        std::cout << "Zamykam Cancel Consultation" << std::endl;
    }

    std::unique_ptr<Request> create(Json::Value) override;

    std::unique_ptr<Serializable> execute() override;

};


#endif //SERVER_CANCELCONSULTATIONREQUEST_H
