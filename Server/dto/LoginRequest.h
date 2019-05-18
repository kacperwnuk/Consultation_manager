//
// Created by Marcin on 29.03.2019.
//

#ifndef SERVER_LOGINREQUEST_H
#define SERVER_LOGINREQUEST_H


#include <string>
#include <jsoncpp/json/value.h>
#include <ostream>
#include "Request.h"

class LoginRequest: public Request {

    struct LoginHelper{
        LoginHelper(){
            Request::addToMap("LoginRequest", new LoginRequest());
        }
    };
    static LoginHelper loginHelper;

    std::string login;
    std::string password;
public:
    const std::string &getLogin() const;

    const std::string &getPassword() const;

    friend std::ostream &operator<<(std::ostream &os, const LoginRequest &request);

    LoginRequest() = default;
    LoginRequest(Json::Value);
    ~LoginRequest(){
        std::cout<<"destruktor login"<<std::endl;
    }
    Request *create(Json::Value) override;

    Serializable *execute() override;
};


#endif //SERVER_LOGINREQUEST_H
