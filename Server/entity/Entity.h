//
// Created by kacper on 04.04.2019.
//

#ifndef SERVER_ENTITY_H
#define SERVER_ENTITY_H

#include <bsoncxx/oid.hpp>
#include <bsoncxx/document/view_or_value.hpp>
#include <jsoncpp/json/json.h>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>

using document_view_or_value = bsoncxx::document::view_or_value;
using oid = bsoncxx::oid;
using b_date = bsoncxx::types::b_date;

class Entity {
public:
    virtual document_view_or_value getDocumentFormat() = 0;
};


#endif //SERVER_ENTITY_H
