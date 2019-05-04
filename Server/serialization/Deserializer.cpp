//
// Created by kacper on 10.04.2019.
//

#include "Deserializer.h"

Deserializer::Deserializer(std::shared_ptr<ClientMessageBuilder> clientMessageBuilder) {
    this->clientMessageBuilder = clientMessageBuilder;
}

RequestType Deserializer::getType() {
    payload = clientMessageBuilder->getMessage();
    Json::Reader reader;
    reader.parse(payload, payloadValue);

    auto requestType = RequestType(payloadValue["type"].asInt());
    return requestType;
}

std::shared_ptr<ClientMessageBuilder> Deserializer::getClientMessageBuilder() {
    return clientMessageBuilder;
}



