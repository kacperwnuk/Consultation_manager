//
// Created by slawek on 29.05.19.
//

#ifndef SERVER_INACTIVEUSERSRESPONSE_H
#define SERVER_INACTIVEUSERSRESPONSE_H


#include "../serialization/Serializable.h"
#include "../entity/AccountInfoForClient.h"

class InactiveUsersResponse : public Serializable{

        std::vector<AccountInfoForClient> inactiveAccounts;
    public:
        InactiveUsersResponse(std::vector<AccountInfoForClient> &inactiveAccounts);
        Json::Value getJson() override;
};


#endif //SERVER_INACTIVEUSERSRESPONSE_H
