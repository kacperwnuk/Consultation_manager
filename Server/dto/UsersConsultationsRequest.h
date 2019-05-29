//
// Created by slawek on 29.05.19.
//

#ifndef SERVER_USERSCONSULTATIONSREQUEST_H
#define SERVER_USERSCONSULTATIONSREQUEST_H


#include "Request.h"

class UsersConsultationsRequest : public Request {

    struct UsersConsultationsRequestHelper {
        UsersConsultationsRequestHelper() {
                std::cout << "Dodaje Users Consultations" << std::endl;
                Request::addToMap("UsersConsultationsRequest", std::make_unique<UsersConsultationsRequest>());
            }
    };

private:
    std::string login;
    static UsersConsultationsRequestHelper helper;

public:
    const std::string &getId() const;

    void setId(const std::string &id);

    const std::string &getLogin() const;

    void setLogin(const std::string &login);

    UsersConsultationsRequest() = default;

    explicit UsersConsultationsRequest(Json::Value);

    ~UsersConsultationsRequest() override {
        std::cout << "Zamykam User Consultation" << std::endl;
    }

    std::unique_ptr<Request> create(Json::Value) override;

    std::unique_ptr<Serializable> execute(Context&) override;
};


#endif //SERVER_USERSCONSULTATIONSREQUEST_H
