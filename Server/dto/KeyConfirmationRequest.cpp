//
// Created by root on 6/3/19.
//

#include "KeyConfirmationRequest.h"
#include "KeyConfirmationResponse.h"
#include "enums/StatusType.h"

KeyConfirmationRequest::KeyConfirmationHelper KeyConfirmationRequest::helper;


KeyConfirmationRequest::KeyConfirmationRequest(Json::Value) {
}

std::unique_ptr<Request> KeyConfirmationRequest::create(Json::Value) {
    std::unique_ptr<Request> request (new KeyConfirmationRequest());
    return std::move(request);}

std::unique_ptr<Serializable> KeyConfirmationRequest::execute(Context & context) {
    std::cout << "Zaczynam potwierdzanie klucza" << std::endl;
    context.confirmKey();
    std::unique_ptr<Serializable> response(new KeyConfirmationResponse(OK));
    return std::move(response);

}
