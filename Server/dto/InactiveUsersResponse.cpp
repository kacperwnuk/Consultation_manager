//
// Created by slawek on 29.05.19.
//

#include "InactiveUsersResponse.h"

InactiveUsersResponse::InactiveUsersResponse(std::vector<AccountInfoForClient> &inactiveAccounts){
    this->inactiveAccounts = inactiveAccounts;
}

Json::Value InactiveUsersResponse::getJson() {
    Json::Value value;
    if (this->inactiveAccounts.empty()){
        value["inactiveUsers"];
    } else {
        for (auto account : inactiveAccounts) {
            value["inactiveUsers"].append(account.getJson());
        }
    }
    value["type"] = "InactiveUsersResponse";
    return value;
}