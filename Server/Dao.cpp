//
// Created by kacper on 03.04.2019.
//
#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <string>
#include "Dao.h"
#include "MongoInstanceContainer.h"

Dao::Dao(const std::string &databaseName): instance(MongoInstanceContainer::getMongoInstanceContainer().getMongoInstance()) {
    db = client[databaseName];
}

void Dao::insertDocument(const document_view_or_value &docValue) {

    coll.insert_one(docValue);

}

void Dao::setCollection(const std::string &collName) {
    coll = db[collName];
}

const mongocxx::collection &Dao::getCollection() const {
    return coll;
}

void Dao::updateDocument(const document_view_or_value &prevDocument, const document_view_or_value &newDocument) {
    coll.replace_one(prevDocument, newDocument);
}

void Dao::deleteDocument(const document_view_or_value &document) {
    coll.delete_one(document);
}

std::vector<Account> Dao::getAccountsByStatusAndRole(AccountStatus accountStatus, AccountRole accountRole) {
    std::vector<Account> students;
    auto result = coll.find(s_document{} << "accountStatus" << accountStatus << "accountRole" << accountRole
                                         << bsoncxx::builder::stream::finalize);
    for (auto studentDoc : result) {
        Account studentAccount = Account(studentDoc);
        students.push_back(studentAccount);
    }
    return students;
}

Account Dao::getAccountByLogin(std::string login) {

    auto results = coll.find(s_document{} << "login" << login << bsoncxx::builder::stream::finalize);
    for(auto result : results){
        return Account(result);
    }
    throw std::runtime_error(std::string("No user with this login!"));
}





