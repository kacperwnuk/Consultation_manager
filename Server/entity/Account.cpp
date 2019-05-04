#include <utility>

#include <utility>

//
// Created by Marcin on 29.03.2019.
//

#include "Account.h"

const bsoncxx::oid &Account::getId() const {
    return id;
}

const std::string &Account::getEmailAddress() const {
    return emailAddress;
}

void Account::setEmailAddress(const std::string &emailAddress) {
    Account::emailAddress = emailAddress;
}

const std::string &Account::getLogin() const {
    return login;
}

void Account::setLogin(const std::string &login) {
    Account::login = login;
}

const std::string &Account::getPasswordHash() const {
    return passwordHash;
}

void Account::setPasswordHash(const std::string &passwordHash) {
    Account::passwordHash = passwordHash;
}

const std::string &Account::getName() const {
    return name;
}

void Account::setName(const std::string &name) {
    Account::name = name;
}

const std::string &Account::getSurname() const {
    return surname;
}

void Account::setSurname(const std::string &surname) {
    Account::surname = surname;
}

AccountRole Account::getAccountRole() const {
    return accountRole;
}

void Account::setRole(AccountRole role) {
    Account::accountRole = role;
}

AccountStatus Account::getAccountStatus() const {
    return accountStatus;
}

void Account::setStatus(AccountStatus accountStatus) {
    Account::accountStatus = accountStatus;
}

Account::Account(std::string email, std::string login, std::string passwordHash,
                 std::string name,
                 std::string surname, AccountRole role, AccountStatus status) : emailAddress(std::move(email)),
                                                                                login(std::move(login)),
                                                                                passwordHash(std::move(passwordHash)),
                                                                                name(std::move(name)),
                                                                                surname(std::move(surname)),
                                                                                accountRole(role),
                                                                                accountStatus(status) {
}

document_view_or_value Account::getDocumentFormat() {
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value docValue = builder
            << "email" << this->emailAddress
            << "login" << this->login
            << "password" << this->passwordHash
            << "name" << this->name
            << "surname" << this->surname
            << "accountRole" << this->accountRole
            << "accountStatus" << this->accountStatus
            << bsoncxx::builder::stream::finalize;

    return docValue;
}

Account::Account(document_view_or_value document) {
    auto stringValue = bsoncxx::to_json(document);
    Json::Reader reader;
    Json::Value jsonValue;
    reader.parse(stringValue, jsonValue);
    this->id = bsoncxx::oid(jsonValue["_id"]["$oid"].asString());
    this->emailAddress = jsonValue["email"].asString();
    this->login = jsonValue["login"].asString();
    this->passwordHash = jsonValue["password"].asString();
    this->name = jsonValue["name"].asString();
    this->surname = jsonValue["surname"].asString();
    this->accountRole = AccountRole(jsonValue["accountRole"].asInt());
    this->accountStatus = AccountStatus(jsonValue["accountStatus"].asInt());
}

Json::Value Account::getJson() {

    Json::Value value;
    value["_id"] = this->id.to_string();
    value["emailAddress"] = this->emailAddress;
    value["login"] = this->login;
    value["passwordHash"] = this->passwordHash;
    value["name"] = this->name;
    value["surname"] = this->surname;
    value["accountRole"] = this->accountRole;
    value["accountStatus"] = this->accountStatus;

    return value;
}



