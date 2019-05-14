//
// Created by kacper on 14.05.2019.
//

#include "Request.h"

void Request::addToMap(std::string s, Request* request) {
    requestMap()[s] = request;
}
