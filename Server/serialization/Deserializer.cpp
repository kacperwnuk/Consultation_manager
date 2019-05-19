//
// Created by kacper on 10.04.2019.
//

#include "Deserializer.h"


std::unique_ptr<Request> Deserializer::getDeserializedObject(const std::string &message) {
    Json::Value jsonValue;
    Json::Reader reader;
    reader.parse(message, jsonValue);
    auto type = jsonValue["type"].asString();
    std::unique_ptr<Request> request = Request::unserialize(type, jsonValue);
    return std::move(request);
}

