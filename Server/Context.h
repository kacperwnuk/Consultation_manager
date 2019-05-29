//
// Created by kacper on 29.05.2019.
//

#ifndef SERVER_CONTEXT_H
#define SERVER_CONTEXT_H


#include "entity/enums/AccountRole.h"
#include "entity/enums/AccountStatus.h"

class Context {

    bool loggedIn;
    AccountRole accountRole;

public:
    Context();
    bool isLogged(){return this->loggedIn;}
    void setLoginStatus(bool);
    AccountRole getAccountRole()const;
    void setAccountRole(AccountRole);

};


#endif //SERVER_CONTEXT_H
