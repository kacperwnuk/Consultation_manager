//
// Created by slawek on 29.05.19.
//

#include "AcceptAccountsRequest.h"
#include "enums/StatusType.h"
#include "AcceptAccountsResponse.h"

AcceptAccountsRequest::AcceptAccountsHelper AcceptAccountsRequest::helper;


AcceptAccountsRequest::AcceptAccountsRequest(Json::Value value) {
    for(Json::Value login : value["logins"]){
        acceptLogins.push_back(login["login"].asString());
    }
}


std::unique_ptr<Request> AcceptAccountsRequest::create(Json::Value value) {
    std::unique_ptr<Request> request (new AcceptAccountsRequest(value));
    return std::move(request);
}


std::unique_ptr<Serializable> AcceptAccountsRequest::execute(Context& context) {

    if (!context.isLogged() || context.getAccountRole() != LECTURER){
        std::unique_ptr<Serializable> response(new AcceptAccountsResponse(ERROR));
        return std::move(response);
    }

    auto dao = Dao::getDaoCollection("TIN", "account");
    try {

        for (auto login : acceptLogins) {
            Account account = dao->getAccountByLogin(login);
            Account newAccount = account;
            newAccount.setStatus(ACTIVE);
            dao->updateDocument(account.getDocumentFormat(), newAccount.getDocumentFormat());
        }
        std::unique_ptr<Serializable> response(new AcceptAccountsResponse(OK));
        return std::move(response);
    } catch (std::exception &e) {
        std::cout << e.what();
        std::unique_ptr<Serializable> response(new AcceptAccountsResponse(ERROR));
        return std::move(response);
    }
}