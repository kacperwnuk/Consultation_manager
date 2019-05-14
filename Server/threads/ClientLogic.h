//
// Created by Marcin on 17.04.2019.
//

#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H


#include <string>
#include "Thread.h"
#include "../ClientMessageBuilder.h"
#include "../serialization/Deserializer.h"
#include "../dto/enums/StatusType.h"
#include "../dto/RegistrationRequest.h"
#include "../containers/OutgoingMessage.h"
#include "../serialization/Serializer.h"
#include "../Dao.h"
#include "../dto/LoginRequest.h"
#include "../entity/Consultation.h"
#include "../dto/NewConsultationRequest.h"
#include "../dto/DailyConsultationsListRequest.h"
#include "../containers/synchronizedcontainers/SynchronizedQueue.h"

class ClientLogic : public Thread {
    SynchronizedQueue<Request*>& inQueue;
    SynchronizedQueue<Serializable*>& outQueue;
    bool &readyToSend;
public:
    ClientLogic(SynchronizedQueue<Request*>&, SynchronizedQueue<Serializable*>&, bool &);

    void run() override;
};


#endif //SERVER_PARSER_H
