//
// Created by kacper on 10.04.2019.
//

#include "Deserializer.h"


Request* Deserializer::getDeserializedObject(const std::string &message) {
    Json::Value jsonValue;
    Json::Reader reader;
    reader.parse(message, jsonValue);
    auto type = jsonValue["type"].asString();
    Request* request = Request::unserialize(type, jsonValue);
    return request;
}

