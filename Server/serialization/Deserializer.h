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
#include "../dto/Request.h"

class Deserializer {

public:
    std::shared_ptr<ClientMessageBuilder> clientMessageBuilder;

    Deserializer(std::shared_ptr<ClientMessageBuilder>);

    Request* getDeserializedObject();

    std::shared_ptr<ClientMessageBuilder> getClientMessageBuilder();

};





#endif //SERVER_DESERIALIZER_H
