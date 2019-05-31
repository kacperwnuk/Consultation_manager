//
// Created by slawek on 29.05.19.
//

#ifndef SERVER_INACTIVEUSERSREQUEST_H
#define SERVER_INACTIVEUSERSREQUEST_H


#include "Request.h"

class InactiveUsersRequest : public Request{

    struct InactiveUsersHelper {
        InactiveUsersHelper() {
            std::cout << "Dodaje Inactive Users" << std::endl;
            Request::addToMap("InactiveUsersRequest", std::make_unique<InactiveUsersRequest>());
        }
    };

    static InactiveUsersHelper helper;

public:

    friend std::ostream &operator<<(std::ostream &os, const InactiveUsersRequest &request);

    InactiveUsersRequest() = default;

    explicit InactiveUsersRequest(Json::Value);

    ~InactiveUsersRequest() override {
        std::cout << "Zamykam inactiveUsers" << std::endl;
    }

    std::unique_ptr<Request> create(Json::Value) override;

    std::unique_ptr<Serializable> execute(Context&) override;
};


#endif //SERVER_INACTIVEUSERSREQUEST_H
