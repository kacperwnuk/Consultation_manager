//
// Created by kacper on 10.04.2019.
//

#ifndef SERVER_DESERIALIZER_H
#define SERVER_DESERIALIZER_H


#include <jsoncpp/json/value.h>

class Deserializer {
public:
    template <typename T>
    T deserialize(Json::Value);
};

template<typename T>
T Deserializer::deserialize(Json::Value jsonValue) {

    return T(jsonValue);
}

#endif //SERVER_DESERIALIZER_H
