//
// Created by slawek on 29.05.19.
//

#include "CancelConsultationRequest.h"
#include "enums/StatusType.h"
#include "CancelConsultationResponse.h"

CancelConsultationRequest::CancelConsultationHelper CancelConsultationRequest::helper;


CancelConsultationRequest::CancelConsultationRequest(Json::Value value) {
    this->id = value["id"].asString();

}


const std::string &CancelConsultationRequest::getId() const {
    return id;
}

void CancelConsultationRequest::setId(const std::string &id) {
    CancelConsultationRequest::id = id;
}


std::unique_ptr<Request> CancelConsultationRequest::create(Json::Value value) {
    std::unique_ptr<Request> request (new CancelConsultationRequest(value));
    return std::move(request);
}


std::unique_ptr<Serializable> CancelConsultationRequest::execute(Context& context) {
    std::cout << "zaczynam anulowac konsultacje" << std::endl;

    if (!context.isLogged()){
        std::unique_ptr<Serializable> response (new CancelConsultationResponse(ERROR));
        return std::move(response);
    }
    auto dao = Dao::getDaoCollection("TIN", "consultation");
    auto dao2 = Dao::getDaoCollection("TIN", "account");
    try {
        auto oldConsultation = dao->getConsultationById(this->getId());

        auto account = context.getAccount();

        AccountInfoForClient info(account.getName(), account.getSurname(), account.getLogin());
         if ((context.getAccountRole() == STUDENT && oldConsultation.getStudent() != info) ||
                 (context.getAccountRole() == LECTURER && oldConsultation.getLecturer() != info)) {
              std::cout << "konsultacja nie nalezy do tego uzytkownika:" << oldConsultation.getStudent() <<  std::endl;
              std::unique_ptr<Serializable> response(new CancelConsultationResponse(ERROR));
              return std::move(response);
          }
        AccountInfoForClient undefined;
        ConsultationStatus newStatus;
         if (context.getAccountRole() == STUDENT) {
             newStatus = FREE;
         } else{
             newStatus = LECTURER_REJECTED;
             undefined = oldConsultation.getStudent();
         }
        Consultation newConsultation(oldConsultation.getLecturer(), oldConsultation.getRoom(), undefined, newStatus,
                                     oldConsultation.getType(), oldConsultation.getConsultationDateStart(),
                                     oldConsultation.getConsultationDateEnd());
        newConsultation.setID(oldConsultation.getId().to_string());

        dao->updateDocument(oldConsultation.getDocumentFormat(), newConsultation.getDocumentFormat());
    } catch (std::exception &e) {
        std::cout << e.what();
        std::unique_ptr<Serializable> response(new CancelConsultationResponse(ERROR));
        return std::move(response);
    }

    std::cout << "Reserwacja pomyślna" << std::endl;
    std::unique_ptr<Serializable> response(new CancelConsultationResponse(OK));
    return std::move(response);


}