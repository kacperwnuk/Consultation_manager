//
// Created by kacper on 29.05.2019.
//

#include "Context.h"

Context::Context() {
    loggedIn = false;
}

AccountRole Context::getAccountRole() const {
    return accountRole;
}

void Context::setAccountRole(AccountRole newAccountRole) {
    this->accountRole = newAccountRole;
}

void Context::setLoginStatus(bool loginStatus) {
    this->loggedIn = loginStatus;
}


