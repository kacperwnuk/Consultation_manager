//
// Created by kacper on 29.05.2019.
//

#include "Context.h"

Context::Context() {
    loggedIn = false;
}

AccountRole Context::getAccountRole() const {
    return account.getAccountRole();
}

void Context::setAccount(Account newAccountRole) {
    this->account = newAccountRole;
}

void Context::setLoginStatus(bool loginStatus) {
    this->loggedIn = loginStatus;
}

AccountStatus Context::getAccountStatus() const {
    return account.getAccountStatus();
}
std::string Context::getLogin() const{
    return account.getLogin();
}
std::string Context::getName() const{
    return account.getName();
}
std::string Context::getSurname() const{
    return account.getSurname();
}
std::string Context::getEmail() const{
    return account.getEmailAddress();
}

Account Context::getAccount() const{
    return account;
}

