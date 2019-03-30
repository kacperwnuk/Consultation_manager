//
// Created by Marcin on 29.03.2019.
//

#include "Account.h"

long long int Account::getId() const {
    return id;
}

void Account::setId(long long int id) {
    Account::id = id;
}

const std::string &Account::getEmailAdress() const {
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
