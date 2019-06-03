//
// Created by root on 6/3/19.
//

#include "KeyResponse.h"
#include <iostream>

KeyResponse::KeyResponse(StatusType toStatus, std::string key): status(toStatus), newKey(key) {

}

Json::Value KeyResponse::getJson() {
    Json::Value value;
    value["status"] = this->status;
    value["type"] = "KeyResponse";
    value["key"] = newKey;
    std::cout << "Mam jsona z nowym klczuem..." << std::endl;
    return value;
}
