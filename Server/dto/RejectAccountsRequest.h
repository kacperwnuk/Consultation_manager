//
// Created by slawek on 31.05.19.
//

#ifndef SERVER_REJECTACCOUNTSREQUEST_H
#define SERVER_REJECTACCOUNTSREQUEST_H


#include "Request.h"

class RejectAccountsRequest  : public Request{

    struct RejectAccountsHelper {
        RejectAccountsHelper() {
            std::cout << "Dodaje RejectAccounts" << std::endl;
            Request::addToMap("RejectAccountsRequest", std::make_unique<RejectAccountsRequest>());
        }
    };

    static RejectAccountsHelper helper;
    std::vector<std::string> acceptLogins;

public:
    friend std::ostream &operator<<(std::ostream &os, const RejectAccountsRequest &request);

    RejectAccountsRequest() = default;

    explicit RejectAccountsRequest(Json::Value);

    ~RejectAccountsRequest() override {
        std::cout << "Zamykam reject accounts" << std::endl;
    }

    std::unique_ptr<Request> create(Json::Value) override;

    std::unique_ptr<Serializable> execute(Context& context) override;
};


#endif //SERVER_REJECTACCOUNTSREQUEST_H
