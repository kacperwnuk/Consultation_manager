//
// Created by kacper on 09.05.2019.
//

#include <bsoncxx/builder/stream/document.hpp>
#include "AccountInfoForClient.h"

Json::Value AccountInfoForClient::getJson() {
    Json::Value value;
    value["name"] = this->name;
    value["surname"] = this->surname;
    value["login"] = this->login;
    return value;
}

AccountInfoForClient::AccountInfoForClient(const std::string &name, const std::string &surname,
                                           const std::string &login) : name(name), surname(surname), login(login) {}

AccountInfoForClient::AccountInfoForClient(Json::Value jsonValue) {
    this->login = jsonValue["login"].asString();
    this->surname = jsonValue["surname"].asString();
    this->name = jsonValue["name"].asString();
}

std::ostream &operator<<(std::ostream &os, const AccountInfoForClient &client) {
    os << " name: " << client.name << " surname: " << client.surname
       << " login: " << client.login;
    return os;
}

bsoncxx::document::view_or_value AccountInfoForClient::getDocumentFormat() {
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value docValue = builder
            << "name" << this->name
            << "surname" << this->surname
            << "login" << this->login
            << bsoncxx::builder::stream::finalize;
    return docValue;
}

AccountInfoForClient::AccountInfoForClient(Account account) {
    this->name = account.getName();
    this->surname = account.getSurname();
    this->login = account.getLogin();
}
