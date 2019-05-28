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


std::unique_ptr<Dao> Dao::getDaoCollection(std::string dbName, std::string collName) {
    auto dao = std::make_unique<Dao>(dbName);
    dao->setCollection(collName);
    return std::move(dao);
}

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

Consultation Dao::getConsultationById(std::string id) {
    oid * searchId = new oid(id);
    std::cout << searchId->to_string() << std::endl;
    auto results = coll.find(s_document{} << "_id" << *searchId << bsoncxx::builder::stream::finalize);
    for (auto result : results) {
        return Consultation(result);
    }
    throw std::runtime_error(std::string("No consultation with this id!"));

}

std::vector<ConsultationInfoForClient> Dao::getConsultationsByDate(b_date dateStart, b_date dateEnd) {

//    auto result = coll.find(s_document{} << "consultationDateStart" << bsoncxx::builder::stream::open_document <<
//                                          "$gte" << dateStart <<
//                                          "$lte" << dateEnd
//                                          << bsoncxx::builder::stream::close_document
//                                          << bsoncxx::builder::stream::finalize);
    auto results = coll.find(
            make_document(kvp("$or",
                              make_array(make_document(kvp("consultationDateStart",
                                                           make_document(kvp("$gte", dateStart),
                                                                         kvp("$lte", dateEnd)))),
                                         make_document(kvp("consultatoinDateEnd",
                                                           make_document(kvp("$gte", dateStart), kvp("$lte", dateEnd))))
                              )
                          )
            ));



    std::vector<ConsultationInfoForClient> consultations;

    for (auto consultationDoc : results) {
        Consultation consultation = Consultation(consultationDoc);
        std::cout << consultation << std::endl;
        auto consultationInfo = ConsultationInfoForClient(
                consultation.getId().to_string(),
                consultation.getLecturer(),
                consultation.getConsultationDateStart(),
                consultation.getConsultationDateEnd(),
                consultation.getRoom(),
                consultation.getConsultationType()
                );
        consultations.push_back(consultationInfo);
    }

    return consultations;
}

void Dao::reserveConsultation(Consultation cons, std::string username)
{
}




