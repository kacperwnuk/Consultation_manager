//
// Created by kacper on 10.04.2019.
//

#ifndef SERVER_SERIALIZER_H
#define SERVER_SERIALIZER_H


#include <string>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <iostream>

class Serializer {
public:
    template<typename T>
    std::string serialize(T);
};

template<typename T>
std::string Serializer::serialize(T element) {

    Json::Value value = element.getJson();
    Json::StyledWriter writer;
    std::string jsonMessage = writer.write(value);
    std::cout << jsonMessage;

    return jsonMessage;
}


#endif //SERVER_SERIALIZER_H
