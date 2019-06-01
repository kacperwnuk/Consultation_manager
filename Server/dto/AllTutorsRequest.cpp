//
// Created by slawek on 01.06.19.
//

#include "AllTutorsRequest.h"
#include "AllTutorsResponse.h"

AllTutorsRequest::AllTutorsHelper AllTutorsRequest::helper;


AllTutorsRequest::AllTutorsRequest(Json::Value value) {
}


std::unique_ptr<Request> AllTutorsRequest::create(Json::Value value) {
    std::unique_ptr<Request> request (new AllTutorsRequest(value));
    return std::move(request);
}


std::unique_ptr<Serializable> AllTutorsRequest::execute(Context& context) {

    if (!context.isLogged()){
        std::vector<AccountInfoForClient> tutorsAccountsInfo;
        std::unique_ptr<Serializable> response (new AllTutorsResponse(tutorsAccountsInfo));
        return std::move(response);
    }

    auto dao = Dao::getDaoCollection("TIN", "account");
    try {
        auto inactiveAccounts = dao->getAccountsByStatusAndRole(ACTIVE, LECTURER);

        std::vector<AccountInfoForClient> inactiveAccountsInfo;
        for (auto account : inactiveAccounts) {
            AccountInfoForClient info(account.getName(), account.getSurname(), account.getLogin());
            inactiveAccountsInfo.push_back(info);
        }
        std::unique_ptr<Serializable> response(new AllTutorsResponse(inactiveAccountsInfo));
        return std::move(response);
    } catch (std::exception &e) {
        std::cout << e.what();
        std::vector<AccountInfoForClient> inactiveAccountsInfo;
        std::unique_ptr<Serializable> response(new AllTutorsResponse(inactiveAccountsInfo));
        return std::move(response);
    }
}