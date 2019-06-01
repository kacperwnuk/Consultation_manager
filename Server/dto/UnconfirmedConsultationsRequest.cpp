//
// Created by slawek on 01.06.19.
//

#include "UnconfirmedConsultationsRequest.h"
#include "UnconfirmedConsultationsResponse.h"


UnconfirmedConsultationsRequest::UnconfirmedConsultationsHelper UnconfirmedConsultationsRequest::helper;

UnconfirmedConsultationsRequest::UnconfirmedConsultationsRequest(Json::Value value) {

}

std::unique_ptr<Request> UnconfirmedConsultationsRequest::create(Json::Value value) {
    std::unique_ptr<Request> request (new UnconfirmedConsultationsRequest(value));
    return std::move(request);
}

std::unique_ptr<Serializable> UnconfirmedConsultationsRequest::execute(Context& context) {

    if (!context.isLogged() || context.getAccountRole() != LECTURER){
        std::unique_ptr<Serializable> response (new UnconfirmedConsultationsResponse(std::vector<ConsultationInfoForClient>()));
        return std::move(response);
    }

    auto dao = Dao::getDaoCollection("TIN", "consultation");

    try {
        AccountInfoForClient info(context.getAccount());
        auto consultations = dao->getUnconfirmedConsultations(info);
        std::unique_ptr<Serializable> response(new UnconfirmedConsultationsResponse(consultations));
        return std::move(response);
    } catch (std::exception &e) {
        std::cout << e.what();
        std::unique_ptr<Serializable> response (new UnconfirmedConsultationsResponse(std::vector<ConsultationInfoForClient>()));
        return std::move(response);
    }


}