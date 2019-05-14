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

Request *LoginRequest::create(Json::Value jsonValue) {
    return new LoginRequest(jsonValue);
}

Serializable *LoginRequest::execute() {
    std::cout<<"Proba logowania"<<std::endl;
    auto dao = Dao::getDaoCollection("TIN", "account");
    try {
        auto account = dao->getAccountByLogin(getLogin());
        if (account.getPasswordHash() != getPassword()) {
            std::cout<<account.getPasswordHash() << " " << getPassword() << std::endl;
            std::cout << "Bad passwd" << std::endl;
            return new LoginResponse(ERROR);
        }
    } catch (std::exception &e) {
        std::cout << e.what();
        return new LoginResponse(ERROR);
    }
    std::cout << "Logowanie pomyślne" << std::endl;
    return new LoginResponse(OK);
}
