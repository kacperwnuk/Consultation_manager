//
// Created by root on 6/3/19.
//

#include "KeyRequest.h"
#include "KeyResponse.h"
#include "enums/StatusType.h"

KeyRequest::KeyHelper KeyRequest::helper;


const std::string &KeyRequest::getKey() const {
    return key;
}

void KeyRequest::setKey(const std::string &key) {
    KeyRequest::key = key;
}

KeyRequest::KeyRequest(Json::Value value) {
    this->key = value["key"].asString();

}

std::unique_ptr<Request> KeyRequest::create(Json::Value value) {
    std::unique_ptr<Request> request (new KeyRequest(value));
    return std::move(request);}

std::unique_ptr<Serializable> KeyRequest::execute(Context & context) {
    std::cout << "Zaczynam uzgadnianie klucza" << std::endl;
    std::string newKey = generateKey();
    context.setNotYetConfirmedKey(newKey);
    std::cout << "Oto nowy klucz: " << newKey << std::endl;
    std::unique_ptr<Serializable> response(new KeyResponse(OK, newKey));
    return std::move(response);
}

std::string KeyRequest::generateKey() {
    auto randchar = []() -> char
    {
        const char charset[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(32,0);
    std::generate_n( str.begin(), 32, randchar );
    return str;
}
