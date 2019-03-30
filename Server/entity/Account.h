//
// Created by Marcin on 29.03.2019.
//

#ifndef SERVER_USER_H
#define SERVER_USER_H


#include <string>
#include "enums/AccountRole.h"
#include "enums/AccountStatus.h"

class Account {
private:
    long long id;
    std::string emailAddress;
    std::string login;
    std::string passwordHash;
    std::string name;
    std::string surname;
    AccountRole accountRole;
    AccountStatus accountStatus;
public:
    long long int getId() const;

    void setId(long long int id);

    const std::string &getEmailAdress() const;

    void setEmailAddress(const std::string &emailAddress);

    const std::string &getLogin() const;

    void setLogin(const std::string &login);

    const std::string &getPasswordHash() const;

    void setPasswordHash(const std::string &passwordHash);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getSurname() const;

    void setSurname(const std::string &surname);

    AccountRole getAccountRole() const;

    void setRole(AccountRole accountRole);

    AccountStatus getAccountStatus() const;

    void setStatus(AccountStatus accountStatus);
};


#endif //SERVER_USER_H
