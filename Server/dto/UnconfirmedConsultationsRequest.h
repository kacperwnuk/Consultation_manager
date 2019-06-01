//
// Created by slawek on 01.06.19.
//

#ifndef SERVER_UNCONFIRMEDCONSULTATIONSREQUEST_H
#define SERVER_UNCONFIRMEDCONSULTATIONSREQUEST_H


#include "Request.h"

class UnconfirmedConsultationsRequest : public Request{
    struct UnconfirmedConsultationsHelper {
        UnconfirmedConsultationsHelper() {
            std::cout << "Dodaje UnconfirmedConsultationsRequest" << std::endl;
            Request::addToMap("UnconfirmedConsultationsRequest", std::make_unique<UnconfirmedConsultationsRequest>());
        }
    };

    static UnconfirmedConsultationsHelper helper;

public:
    UnconfirmedConsultationsRequest() = default;

    UnconfirmedConsultationsRequest(Json::Value);

    ~UnconfirmedConsultationsRequest() override {
        std::cout << "Zamykam UnconfirmedConsultationsRequest" << std::endl;
    }

    std::unique_ptr<Request> create(Json::Value) override;

    std::unique_ptr<Serializable> execute(Context&) override;
};


#endif //SERVER_UNCONFIRMEDCONSULTATIONSREQUEST_H
