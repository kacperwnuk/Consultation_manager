//
// Created by slawek on 31.05.19.
//

#include "AcceptConsultationRequest.h"
#include "AcceptConsultationResponse.h"

AcceptConsultationRequest::AcceptConsultationHelper AcceptConsultationRequest::helper;


AcceptConsultationRequest::AcceptConsultationRequest(Json::Value value) {
    this->id = value["id"].asString();
}


const std::string &AcceptConsultationRequest::getId() const {
    return id;
}

void AcceptConsultationRequest::setId(const std::string &id) {
    AcceptConsultationRequest::id = id;
}

std::unique_ptr<Request> AcceptConsultationRequest::create(Json::Value value) {
    std::unique_ptr<Request> request (new AcceptConsultationRequest(value));
    return std::move(request);
}


std::unique_ptr<Serializable> AcceptConsultationRequest::execute(Context& context) {
    if (!context.isLogged()){
        std::unique_ptr<Serializable> response (new AcceptConsultationResponse(ERROR));
        return std::move(response);
    }
    auto dao = Dao::getDaoCollection("TIN", "consultation");
    try {
        auto oldConsultation = dao->getConsultationById(this->getId());

        AccountInfoForClient info(context.getAccount());
        if (oldConsultation.getLecturer() != info) {
            std::cout << "konsultacja nie nalezy do tego tutora:" << oldConsultation.getLecturer() <<  std::endl;
            std::unique_ptr<Serializable> response(new AcceptConsultationResponse(ERROR));
            return std::move(response);
        }

        Consultation newConsultation(oldConsultation.getLecturer(), oldConsultation.getRoom(),oldConsultation.getStudent(), STUDENT_BOOKED,
                                     oldConsultation.getType(), oldConsultation.getConsultationDateStart(),
                                     oldConsultation.getConsultationDateEnd());

        newConsultation.setID(oldConsultation.getId().to_string());

        dao->updateDocument(oldConsultation.getDocumentFormat(), newConsultation.getDocumentFormat());
    } catch (std::exception &e) {
        std::cout << e.what();
        std::unique_ptr<Serializable> response(new AcceptConsultationResponse(ERROR));
        return std::move(response);
    }

    std::unique_ptr<Serializable> response(new AcceptConsultationResponse(OK));
    return std::move(response);


}