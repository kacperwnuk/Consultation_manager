//
// Created by slawek on 01.06.19.
//

#ifndef SERVER_ALLTUTORSRESPONSE_H
#define SERVER_ALLTUTORSRESPONSE_H


#include "../serialization/Serializable.h"
#include "../entity/AccountInfoForClient.h"

class AllTutorsResponse  : public Serializable{

    std::vector<AccountInfoForClient> tutorsAccounts;
public:
    AllTutorsResponse(std::vector<AccountInfoForClient>&);
    Json::Value getJson() override;
};


#endif //SERVER_ALLTUTORSRESPONSE_H
