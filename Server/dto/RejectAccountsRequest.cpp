//
// Created by slawek on 31.05.19.
//

#include "RejectAccountsRequest.h"
#include "enums/StatusType.h"
#include "RejectAccountsResponse.h"

RejectAccountsRequest::RejectAccountsHelper RejectAccountsRequest::helper;


RejectAccountsRequest::RejectAccountsRequest(Json::Value value) {
    for(Json::Value login : value["logins"]){
        acceptLogins.push_back(login["login"].asString());
    }
}


std::unique_ptr<Request> RejectAccountsRequest::create(Json::Value value) {
    std::unique_ptr<Request> request (new RejectAccountsRequest(value));
    return std::move(request);
}


std::unique_ptr<Serializable> RejectAccountsRequest::execute(Context& context) {

    if (!context.isLogged() || context.getAccountRole() != LECTURER){
        std::unique_ptr<Serializable> response(new RejectAccountsResponse(ERROR));
        return std::move(response);
    }

    auto dao = Dao::getDaoCollection("TIN", "account");
    try {

        for (auto login : acceptLogins) {
            Account account = dao->getAccountByLogin(login);
            dao->deleteDocument(account.getDocumentFormat());
        }
        std::unique_ptr<Serializable> response(new RejectAccountsResponse(OK));
        return std::move(response);
    } catch (std::exception &e) {
        std::cout << e.what();
        std::unique_ptr<Serializable> response(new RejectAccountsResponse(ERROR));
        return std::move(response);
    }
}