//
// Created by Marcin on 29.03.2019.
//

#include "LoginRequest.h"

LoginRequest::LoginRequest(Json::Value value) {
    this->login = value["login"].asString();
    this->password = value["password"].asString();
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
