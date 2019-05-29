//
// Created by slawek on 29.05.19.
//

#include "InactiveUsersRequest.h"
#include "InactiveUsersResponse.h"

InactiveUsersRequest::InactiveUsersHelper InactiveUsersRequest::helper;


InactiveUsersRequest::InactiveUsersRequest(Json::Value value) {


}


std::unique_ptr<Request> InactiveUsersRequest::create(Json::Value value) {
    std::unique_ptr<Request> request (new InactiveUsersRequest(value));
    return std::move(request);
}


std::unique_ptr<Serializable> InactiveUsersRequest::execute(Context& context) {

    if (!context.isLogged() || context.getAccountRole() != LECTURER){
        std::vector<AccountInfoForClient> inactiveAccountsInfo;
        std::unique_ptr<Serializable> response (new InactiveUsersResponse(inactiveAccountsInfo));
        return std::move(response);
    }

    auto dao = Dao::getDaoCollection("TIN", "account");
    try {
        auto inactiveAccounts = dao->getAccountsByStatusAndRole(INACTIVE, STUDENT);

        std::vector<AccountInfoForClient> inactiveAccountsInfo;
        for (auto account : inactiveAccounts) {
            AccountInfoForClient info(account.getName(), account.getSurname(), account.getLogin());
            inactiveAccountsInfo.push_back(info);
        }
        std::unique_ptr<Serializable> response(new InactiveUsersResponse(inactiveAccountsInfo));
        return std::move(response);
    } catch (std::exception &e) {
        std::cout << e.what();
        std::vector<AccountInfoForClient> inactiveAccountsInfo;
        std::unique_ptr<Serializable> response(new InactiveUsersResponse(inactiveAccountsInfo));
        return std::move(response);
    }
}