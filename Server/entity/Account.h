//
// Created by Marcin on 29.03.2019.
//

#ifndef SERVER_USER_H
#define SERVER_USER_H


#include <string>
#include <bsoncxx/document/view_or_value.hpp>
#include "enums/AccountRole.h"
#include "enums/AccountStatus.h"
#include "Entity.h"
#include "../serialization/Serializable.h"

class Account: public Entity, public Serializable {
private:

    oid id;
    std::string emailAddress;
    std::string login;
    std::string passwordHash;
    std::string name;
    std::string surname;
    AccountRole accountRole;
    AccountStatus accountStatus;

public:

    Account(std::string, std::string, std::string, std::string, std::string, AccountRole, AccountStatus);

    Account(document_view_or_value);

    document_view_or_value getDocumentFormat() override;

    const bsoncxx::oid &getId() const;

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

    Json::Value getJson() override;
};


#endif //SERVER_USER_H
