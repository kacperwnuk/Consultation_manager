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

Dao::Dao(const std::string &databaseName) : instance(
        MongoInstanceContainer::getMongoInstanceContainer().getMongoInstance()) {
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
    for (auto result : results) {
        return Account(result);
    }
    throw std::runtime_error(std::string("No user with this login!"));
}

std::vector<Consultation> Dao::getConsultationsByDate(b_date date) {

    std::cout<< date.value.count() << std::endl;
    auto dayAfter = std::chrono::milliseconds(date.value.count() + std::chrono::milliseconds(std::chrono::hours(24)).count());
    auto results = coll.find(s_document{} << "consultationDate" << bsoncxx::builder::stream::open_document <<
                                          "$gt" << date <<
                                          "$lte" << b_date(dayAfter)
                                          << bsoncxx::builder::stream::close_document
                                          << bsoncxx::builder::stream::finalize);
    std::vector<Consultation> consultations;
    for (auto consultationDoc : results) {
        Consultation consultation = Consultation(consultationDoc);
        std::cout << consultation << std::endl;
        consultations.push_back(consultation);
    }

    return consultations;
}





