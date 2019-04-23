//
// Created by kacper on 10.04.2019.
//

#ifndef SERVER_DESERIALIZER_H
#define SERVER_DESERIALIZER_H

#include <memory>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include "../ClientMessageBuilder.h"
#include "../dto/enums/RequestType.h"

class Deserializer {
    std::string payload;
    Json::Value payloadValue;
public:
    std::shared_ptr<ClientMessageBuilder> clientMessageBuilder;

    Deserializer(std::shared_ptr<ClientMessageBuilder>);

    RequestType getType();

    template<typename T>
    T deserializedObject();

    template<typename T>
    T deserialize(Json::Value);

    std::shared_ptr<ClientMessageBuilder> getClientMessageBuilder();

};

template<typename T>
T Deserializer::deserialize(Json::Value jsonValue) {

    return T(jsonValue);
}

template<typename T>
T Deserializer::deserializedObject() {

    return deserialize<T>(payloadValue);
}


#endif //SERVER_DESERIALIZER_H
