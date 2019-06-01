//
// Created by slawek on 01.06.19.
//

#include "AllTutorsResponse.h"

AllTutorsResponse::AllTutorsResponse(std::vector<AccountInfoForClient> &tutorsAccounts){
    this->tutorsAccounts = tutorsAccounts;
}

Json::Value AllTutorsResponse::getJson() {
    Json::Value value;
    if (this->tutorsAccounts.empty()){
        value["tutors"];
    } else {
        for (auto account : tutorsAccounts) {
            value["tutors"].append(account.getJson());
        }
    }
    value["type"] = "AllTutorsResponse";
    return value;
}