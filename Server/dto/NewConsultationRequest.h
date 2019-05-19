//
// Created by kacper on 07.05.2019.
//

#ifndef SERVER_NEWCONSULTATIONREQUEST_H
#define SERVER_NEWCONSULTATIONREQUEST_H


#include <ostream>
#include "../entity/Consultation.h"
#include "../entity/ConsultationInfoForClient.h"
#include "Request.h"

class NewConsultationRequest : public Request {

    struct NewConsultationHelper {
        NewConsultationHelper() {
            std::cout << "Dodaje NewRegistration" << std::endl;
            Request::addToMap("NewConsultationRequest", std::make_unique<NewConsultationRequest>());
        }
    };

    static NewConsultationHelper newConsultationHelper;

    ConsultationInfoForClient consultationInfo;

public:
    const ConsultationInfoForClient &getConsultationInfo() const;

    friend std::ostream &operator<<(std::ostream &os, const NewConsultationRequest &request);

    b_date getConsultationDateStart();

    NewConsultationRequest() = default;

    NewConsultationRequest(Json::Value);

    ~NewConsultationRequest() override {
        std::cout << "Zamykam New" << std::endl;
    }

    b_date getConsultationDateEnd();

    std::unique_ptr<Request> create(Json::Value value) override;

    std::unique_ptr<Serializable> execute() override;
};


#endif //SERVER_NEWCONSULTATIONREQUEST_H
