//
// Created by Marcin on 29.03.2019.
//

#include <iostream>
#include "LoginRequest.h"
#include "enums/StatusType.h"
#include "LoginResponse.h"

LoginRequest::LoginHelper LoginRequest::loginHelper;


LoginRequest::LoginRequest(Json::Value value) {
    this->login = value["login"].asString();
    this->password = value["passwordHash"].asString();
}

std::ostream &operator<<(std::ostream &os, const LoginRequest &request) {
    os << "login: " << request.login << " password: " << request.password;
    return os;
}

const std::string &LoginRequest::getLogin() const {
    return login;
}

const std::string &LoginRequest::getPassword() const {
    return password;
}

std::unique_ptr<Request> LoginRequest::create(Json::Value jsonValue) {
    std::unique_ptr<Request> request (new LoginRequest(jsonValue));
    return std::move(request);
}

std::unique_ptr<Serializable> LoginRequest::execute(Context& context) {
    std::cout<<"Proba logowania"<<std::endl;
    auto dao = Dao::getDaoCollection("TIN", "account");
    try {
        auto account = dao->getAccountByLogin(getLogin());
        //if (account.getPasswordHash() != getPassword() || account.getAccountStatus() == AccountStatus::INACTIVE) { //w final version to odkomentowac a wywalic to ponizej
        if (account.getPasswordHash() != getPassword()) {

            std::cout<<account.getPasswordHash() << " " << getPassword() << std::endl;
            std::cout << "Bad passwd lub niezatwierdzony" << std::endl;
            std::unique_ptr<Serializable> response (new LoginResponse(ERROR));
            return std::move(response);
        } else {
            context.setLoginStatus(true);
            context.setAccountRole(account.getAccountRole());
        }
    } catch (std::exception &e) {
        std::cout << e.what();
        std::unique_ptr<Serializable> response (new LoginResponse(ERROR));
        return std::move(response);
    }
    std::cout << "Logowanie pomyślne" << std::endl;
    std::unique_ptr<Serializable> response (new LoginResponse(OK, context.getAccountRole()));
    return std::move(response);
}
