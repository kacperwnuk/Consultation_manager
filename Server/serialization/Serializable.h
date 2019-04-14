//
// Created by kacper on 10.04.2019.
//

#ifndef SERVER_SERIALIZABLE_H
#define SERVER_SERIALIZABLE_H


#include <jsoncpp/json/value.h>

class Serializable{
public:
    virtual Json::Value getJson() = 0;
};




#endif //SERVER_SERIALIZABLE_H
