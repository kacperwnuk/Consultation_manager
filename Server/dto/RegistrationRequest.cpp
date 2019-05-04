//
// Created by kacper on 19.04.2019.
//

#include "RegistrationRequest.h"

RegistrationRequest::RegistrationRequest(Json::Value value) {
    this->email = value["email"].asString();
    this->login = value["login"].asString();
    this->password = value["password"].asString();
    this->name = value["name"].asString();
    this->surname = value["surname"].asString();
    this->accountRole = AccountRole(value["accountRole"].asInt());
}

std::ostream &operator<<(std::ostream &os, const RegistrationRequest &request) {
    os << "login: " << request.login << " password: " << request.password << " email: " << request.email;
    return os;
}

const std::string &RegistrationRequest::getEmail() const {
    return email;
}

const std::string &RegistrationRequest::getLogin() const {
    return login;
}

const std::string &RegistrationRequest::getPassword() const {
    return password;
}

const std::string &RegistrationRequest::getName() const {
    return name;
}

const std::string &RegistrationRequest::getSurname() const {
    return surname;
}

AccountRole RegistrationRequest::getAccountRole() const {
    return accountRole;
}
