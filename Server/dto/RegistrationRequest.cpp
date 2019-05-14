//
// Created by kacper on 19.04.2019.
//

#include <iostream>
#include "RegistrationRequest.h"
#include "enums/StatusType.h"
#include "RegistrationResponse.h"

RegistrationRequest::RegistrationHelper RegistrationRequest::registrationHelper;

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

Request *RegistrationRequest::create(Json::Value value) {
    return new RegistrationRequest(value);
}

Serializable *RegistrationRequest::execute() {
    auto account = Account(getEmail(), getLogin(), getPassword(), getName(),
                           getSurname(), getAccountRole(), AccountStatus::INACTIVE);
    auto document = account.getDocumentFormat();
    auto dao = Dao::getDaoCollection("TIN", "account");

    try {
        dao->insertDocument(document);
    }
    catch (std::exception &e) {
        std::cout << e.what();
        return new RegistrationResponse(ERROR);
    }
    std::cout << "Rejestracja pomyślna" << std::endl;
    return new RegistrationResponse(OK);


}
