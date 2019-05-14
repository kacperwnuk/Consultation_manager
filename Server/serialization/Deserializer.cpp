//
// Created by kacper on 10.04.2019.
//

#include "Deserializer.h"

Deserializer::Deserializer(std::shared_ptr<ClientMessageBuilder> clientMessageBuilder) {
    this->clientMessageBuilder = clientMessageBuilder;
}

std::shared_ptr<ClientMessageBuilder> Deserializer::getClientMessageBuilder() {
    return clientMessageBuilder;
}

Request* Deserializer::getDeserializedObject() {
    auto newPayload = clientMessageBuilder->getMessage();
    Json::Value jsonValue;
    Json::Reader reader;
    reader.parse(newPayload, jsonValue);
    auto type = jsonValue["type"].asString();
    Request* request = Request::unserialize(type, jsonValue);
    return request;
}

