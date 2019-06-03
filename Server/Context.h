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
    std::string key = "adamsobieski1234adamsobieski1234";
    std::string notYetConfirmedKey;
public:
    const std::string &getNotYetConfirmedKey() const;

    void setNotYetConfirmedKey(const std::string &notYetConfirmedKey);

public:
    const std::string &getKey() const;

    void setKey(const std::string &key);


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
    void confirmKey() {
        key = notYetConfirmedKey;
        notYetConfirmedKey = "";
    }

};


#endif //SERVER_CONTEXT_H
