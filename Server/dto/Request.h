#include <utility>

//
// Created by kacper on 14.05.2019.
//

#ifndef SERVER_REQUEST_H
#define SERVER_REQUEST_H


#include <string>
#include <map>
#include <iostream>
#include "../serialization/Serializable.h"
#include "../Dao.h"
#include "../Context.h"

class Request {
protected:
    static std::map<std::string, std::unique_ptr<Request>>& requestMap(){
        static std::map<std::string, std::unique_ptr<Request>> _rm;
         return _rm;
    }

public:
    virtual std::unique_ptr<Request> create(Json::Value) = 0;
    virtual std::unique_ptr<Serializable> execute(Context&) = 0;
    virtual ~Request(){}

    static std::unique_ptr<Request> unserialize(std::string classType, Json::Value payload){
        if (requestMap().count(classType) != 0){
            return std::move(requestMap()[classType]->create(payload));
        }
        return nullptr;
    }

    static void addToMap(std::string, std::unique_ptr<Request>);

};


#endif //SERVER_REQUEST_H
