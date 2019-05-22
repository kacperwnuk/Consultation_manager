//
// Created by kacper on 14.05.2019.
//

#include "Request.h"

void Request::addToMap(std::string s, std::unique_ptr<Request> request) {
    requestMap()[s] = std::move(request);
}
