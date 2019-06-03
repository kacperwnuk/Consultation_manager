//
// Created by root on 6/3/19.
//

#ifndef SERVER_KEYCONFIRMATIONREQUEST_H
#define SERVER_KEYCONFIRMATIONREQUEST_H

#include "Request.h"

class KeyConfirmationRequest: public Request {
    struct KeyConfirmationHelper {
        KeyConfirmationHelper() {
            std::cout << "Dodaje keyConfirmation" << std::endl;
            Request::addToMap("KeyConfirmationRequest", std::make_unique<KeyConfirmationRequest>());
        }
    };

private:
    static KeyConfirmationHelper helper;
public:


    KeyConfirmationRequest() = default;

    explicit KeyConfirmationRequest(Json::Value);

    ~KeyConfirmationRequest() override {
        std::cout << "Zamykam KeyConfirmation" << std::endl;
    }

    std::unique_ptr<Request> create(Json::Value) override;

    std::unique_ptr<Serializable> execute(Context&) override;



};


#endif //SERVER_KEYCONFIRMATIONREQUEST_H
