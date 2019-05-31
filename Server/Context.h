//
// Created by kacper on 29.05.2019.
//

#ifndef SERVER_CONTEXT_H
#define SERVER_CONTEXT_H


#include "entity/enums/AccountRole.h"
#include "entity/enums/AccountStatus.h"
#include "entity/Account.h"

class Context {

    bool loggedIn;
    Account account;

public:
    Context();
    bool isLogged(){return this->loggedIn;}
    void setLoginStatus(bool);
    AccountRole getAccountRole()const;
    AccountStatus getAccountStatus()const;
    std::string getLogin() const;
    std::string getName() const;
    std::string getSurname() const;
    std::string getEmail() const;
    void setAccount(Account);
    Account getAccount() const;

};


#endif //SERVER_CONTEXT_H
