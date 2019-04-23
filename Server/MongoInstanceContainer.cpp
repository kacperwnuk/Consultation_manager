//
// Created by Marcin on 23.04.2019.
//

#include "MongoInstanceContainer.h"

MongoInstanceContainer::MongoInstanceContainer(mongocxx::instance &instance): instance(instance) {

}

MongoInstanceContainer &MongoInstanceContainer::getMongoInstanceContainer() {
    static mongocxx::instance instance{};
    static MongoInstanceContainer mongoInstanceContainer(instance);
    return mongoInstanceContainer;
}

mongocxx::instance& MongoInstanceContainer::getMongoInstance() {
    return instance;
}
