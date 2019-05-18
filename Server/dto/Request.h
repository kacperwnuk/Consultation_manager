#include <utility>

//
// Created by kacper on 14.05.2019.
//

#ifndef SERVER_REQUEST_H
#define SERVER_REQUEST_H


#include <string>
#include <map>
#include "../serialization/Serializable.h"
#include "../Dao.h"

class Request {
protected:
    static std::map<std::string, Request*>& requestMap(){
        static std::map<std::string, Request*> _rm;
        return _rm;
    }

public:
    virtual Request* create(Json::Value) = 0;
    virtual Serializable* execute() = 0;
    virtual ~Request(){}

    static Request* unserialize(std::string classType, Json::Value payload){
        if (requestMap().count(classType) != 0){
            return requestMap()[classType]->create(std::move(payload));
        }
        return nullptr;
    }

    static void addToMap(std::string, Request*);

};


#endif //SERVER_REQUEST_H
