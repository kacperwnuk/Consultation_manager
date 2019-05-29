//
// Created by slawek on 29.05.19.
//

#ifndef SERVER_ACCEPTACCOUNTSREQUEST_H
#define SERVER_ACCEPTACCOUNTSREQUEST_H


#include "Request.h"

class AcceptAccountsRequest : public Request{

    struct AcceptAccountsHelper {
        AcceptAccountsHelper() {
            std::cout << "Dodaje AcceptAccounts" << std::endl;
            Request::addToMap("AcceptAccountsRequest", std::make_unique<AcceptAccountsRequest>());
        }
    };

    static AcceptAccountsHelper helper;
    std::vector<std::string> acceptLogins;

public:
    friend std::ostream &operator<<(std::ostream &os, const AcceptAccountsRequest &request);

    AcceptAccountsRequest() = default;

    explicit AcceptAccountsRequest(Json::Value);

    ~AcceptAccountsRequest() override {
        std::cout << "Zamykam registration" << std::endl;
    }

    std::unique_ptr<Request> create(Json::Value) override;

    std::unique_ptr<Serializable> execute(Context& context) override;
};


#endif //SERVER_ACCEPTACCOUNTSREQUEST_H
