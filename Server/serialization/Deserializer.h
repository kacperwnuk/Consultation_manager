//
// Created by kacper on 10.04.2019.
//

#ifndef SERVER_DESERIALIZER_H
#define SERVER_DESERIALIZER_H

#include <memory>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include "../dto/Request.h"

class Deserializer {
public:
    Request* getDeserializedObject(const std::string &message);
};





#endif //SERVER_DESERIALIZER_H
