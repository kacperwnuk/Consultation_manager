//
// Created by Marcin on 29.03.2019.
//

#ifndef SERVER_LOGINREQUEST_H
#define SERVER_LOGINREQUEST_H


#include <string>
#include <jsoncpp/json/value.h>
#include <ostream>

class LoginRequest {
private:
    std::string login;
    std::string password;
public:
    const std::string &getLogin() const;

    const std::string &getPassword() const;

    friend std::ostream &operator<<(std::ostream &os, const LoginRequest &request);

    LoginRequest(Json::Value);
};


#endif //SERVER_LOGINREQUEST_H
