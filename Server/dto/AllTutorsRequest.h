//
// Created by slawek on 01.06.19.
//

#ifndef SERVER_ALLTUTORSREQUEST_H
#define SERVER_ALLTUTORSREQUEST_H


#include "Request.h"

class AllTutorsRequest : public Request{

    struct AllTutorsHelper {
        AllTutorsHelper() {
            std::cout << "Dodaje all tutors" << std::endl;
            Request::addToMap("AllTutorsRequest", std::make_unique<AllTutorsRequest>());
        }
    };

    static AllTutorsHelper helper;

public:

    friend std::ostream &operator<<(std::ostream &os, const AllTutorsRequest &request);

    AllTutorsRequest() = default;

    explicit AllTutorsRequest(Json::Value);

    ~AllTutorsRequest() override {
        std::cout << "Zamykam all tutor request" << std::endl;
    }

    std::unique_ptr<Request> create(Json::Value) override;

    std::unique_ptr<Serializable> execute(Context&) override;
};


#endif //SERVER_ALLTUTORSREQUEST_H
