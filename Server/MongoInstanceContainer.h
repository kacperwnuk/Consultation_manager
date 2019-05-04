//
// Created by Marcin on 23.04.2019.
//

#ifndef SERVER_MONGOINSTANCE_H
#define SERVER_MONGOINSTANCE_H

#include <mongocxx/instance.hpp>


class MongoInstanceContainer {
private:
    explicit MongoInstanceContainer(mongocxx::instance &);

    mongocxx::instance &instance;
public:
    static MongoInstanceContainer &getMongoInstanceContainer();

    mongocxx::instance &getMongoInstance();
};


#endif //SERVER_MONGOINSTANCE_H
