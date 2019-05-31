//
// Created by slawek on 31.05.19.
//

#ifndef SERVER_REJECTCONSULTATIONREQUEST_H
#define SERVER_REJECTCONSULTATIONREQUEST_H


#include "Request.h"

class RejectConsultationRequest : public Request {

    struct RejectConsultationHelper {
        RejectConsultationHelper() {
            std::cout << "Dodaje RejectConsultation" << std::endl;
            Request::addToMap("RejectConsultationRequest", std::make_unique<RejectConsultationRequest>());
        }
    };

private:
    std::string id;
    static RejectConsultationHelper helper;

public:
    const std::string &getId() const;

    void setId(const std::string &id);

    RejectConsultationRequest() = default;

    explicit RejectConsultationRequest(Json::Value);

    ~RejectConsultationRequest() override {
        std::cout << "Zamykam Cancel Consultation" << std::endl;
    }

    std::unique_ptr<Request> create(Json::Value) override;

    std::unique_ptr<Serializable> execute(Context&) override;

};

#endif //SERVER_REJECTCONSULTATIONREQUEST_H
