//
// Created by kacper on 07.05.2019.
//

#ifndef SERVER_NEWCONSULTATIONREQUEST_H
#define SERVER_NEWCONSULTATIONREQUEST_H


#include <ostream>
#include "../entity/Consultation.h"

class NewConsultationRequest {
private:
    Consultation consultation;
public:
    bsoncxx::document::view_or_value getConsultationDocumentFormat();
    friend std::ostream &operator<<(std::ostream &os, const NewConsultationRequest &request);

    NewConsultationRequest(Json::Value);
};


#endif //SERVER_NEWCONSULTATIONREQUEST_H
