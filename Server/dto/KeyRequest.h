//
// Created by root on 6/3/19.
//

#ifndef SERVER_KEYREQUEST_H
#define SERVER_KEYREQUEST_H

#include "Request.h"


class KeyRequest: public Request {
    struct KeyHelper {
        KeyHelper() {
            std::cout << "Dodaje key" << std::endl;
            Request::addToMap("KeyRequest", std::make_unique<KeyRequest>());
        }
    };

private:
    std::string key;
    static KeyHelper helper;
public:
    const std::string &getKey() const;

    void setKey(const std::string &key);

    KeyRequest() = default;

    explicit KeyRequest(Json::Value);

    ~KeyRequest() override {
        std::cout << "Zamykam Key" << std::endl;
    }

    std::unique_ptr<Request> create(Json::Value) override;

    std::unique_ptr<Serializable> execute(Context&) override;

    std::string generateKey();

public:

};


#endif //SERVER_KEYREQUEST_H
