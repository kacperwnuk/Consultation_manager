//
// Created by slawek on 31.05.19.
//

#include "RejectConsultationRequest.h"
#include "../entity/enums/ConsultationStatus.h"
#include "RejectConsultationResponse.h"

RejectConsultationRequest::RejectConsultationHelper RejectConsultationRequest::helper;


RejectConsultationRequest::RejectConsultationRequest(Json::Value value) {
    this->id = value["id"].asString();

}


const std::string &RejectConsultationRequest::getId() const {
    return id;
}

void RejectConsultationRequest::setId(const std::string &id) {
    RejectConsultationRequest::id = id;
}

std::unique_ptr<Request> RejectConsultationRequest::create(Json::Value value) {
    std::unique_ptr<Request> request (new RejectConsultationRequest(value));
    return std::move(request);
}


std::unique_ptr<Serializable> RejectConsultationRequest::execute(Context& context) {

    if (!context.isLogged()){
        std::unique_ptr<Serializable> response (new RejectConsultationResponse(ERROR));
        return std::move(response);
    }
    auto dao = Dao::getDaoCollection("TIN", "consultation");
    try {
        auto oldConsultation = dao->getConsultationById(this->getId());


        AccountInfoForClient info(context.getAccount());
        if (oldConsultation.getLecturer() != info) {
            std::cout << "konsultacja nie nalezy do tego tutora:" << oldConsultation.getLecturer() <<  std::endl;
            std::unique_ptr<Serializable> response(new RejectConsultationResponse(ERROR));
            return std::move(response);
        }

        Consultation newConsultation(oldConsultation.getLecturer(), oldConsultation.getRoom(),oldConsultation.getStudent(), LECTURER_REJECTED,
                                     oldConsultation.getType(), oldConsultation.getConsultationDateStart(),
                                     oldConsultation.getConsultationDateEnd());

        newConsultation.setID(oldConsultation.getId().to_string());

        dao->updateDocument(oldConsultation.getDocumentFormat(), newConsultation.getDocumentFormat());
    } catch (std::exception &e) {
        std::cout << e.what();
        std::unique_ptr<Serializable> response(new RejectConsultationResponse(ERROR));
        return std::move(response);
    }

    std::unique_ptr<Serializable> response(new RejectConsultationResponse(OK));
    return std::move(response);


}