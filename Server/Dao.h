//
// Created by kacper on 03.04.2019.
//

#ifndef SERVER_DAO_H
#define SERVER_DAO_H


#include <string>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include "entity/enums/AccountStatus.h"
#include "entity/Account.h"
#include "entity/Consultation.h"

using bsoncxx::builder::stream::close_array;
using s_document = bsoncxx::builder::stream::document;
using document_view_or_value = bsoncxx::document::view_or_value;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::basic::make_document;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;

class Dao {
private:

    mongocxx::instance &instance; // This should be done only once.
    mongocxx::client client{mongocxx::uri{}};
    mongocxx::database db;
    mongocxx::collection coll;
public:

    const mongocxx::collection &getCollection() const;

    explicit Dao(const std::string &);

    void insertDocument(const document_view_or_value &);

    void setCollection(const std::string &);

    template<typename T>
    void updateDocument(const document_view_or_value &, const std::string &, T);

    void updateDocument(const document_view_or_value &, const document_view_or_value &);

    void deleteDocument(const document_view_or_value &);

    std::vector<Account> getAccountsByStatusAndRole(AccountStatus, AccountRole);

    Account getAccountByLogin(std::string login);

    std::vector<Consultation> getConsultationsByDate(b_date, b_date);
};

template<typename T>
void Dao::updateDocument(const document_view_or_value &prevDocument, const std::string &attribute, T value) {
    coll.update_one(prevDocument, s_document{} << "$set" << bsoncxx::builder::stream::open_document
                                               << attribute << value << bsoncxx::builder::stream::close_document
                                               << bsoncxx::builder::stream::finalize);
}

#endif //SERVER_DAO_H
