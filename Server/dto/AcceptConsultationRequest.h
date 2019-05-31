//
// Created by slawek on 31.05.19.
//

#ifndef SERVER_ACCEPTCONSULTATIONREQUEST_H
#define SERVER_ACCEPTCONSULTATIONREQUEST_H


#include "Request.h"
#include "CancelConsultationRequest.h"

class AcceptConsultationRequest : public Request {

        struct AcceptConsultationHelper {
            AcceptConsultationHelper() {
                std::cout << "Dodaje AcceptConsultation" << std::endl;
                Request::addToMap("AcceptConsultationRequest", std::make_unique<AcceptConsultationRequest>());
            }
        };

        private:
        std::string id;
        static AcceptConsultationHelper helper;

        public:
        const std::string &getId() const;

        void setId(const std::string &id);

        AcceptConsultationRequest() = default;

        explicit AcceptConsultationRequest(Json::Value);

        ~AcceptConsultationRequest() override {
                std::cout << "Zamykam Accept Consultation" << std::endl;
        }

        std::unique_ptr<Request> create(Json::Value) override;

        std::unique_ptr<Serializable> execute(Context&) override;

};


#endif //SERVER_ACCEPTCONSULTATIONREQUEST_H
