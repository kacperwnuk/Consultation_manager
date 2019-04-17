//
// Created by Marcin on 17.04.2019.
//

#include "ClientLogic.h"

void ClientLogic::run() {
    bool isRunning = true;
    while(isRunning) {
        std::cout << "Logika zwrocila " << clientMessageBuilder->getMessage() << std::endl;
    }
}

ClientLogic::ClientLogic(int socket, MutualExclusiveHashMap<size_t> &readDemands): socket(socket), readDemands(readDemands) {
    clientMessageBuilder = new ClientMessageBuilder(socket, readDemands);
}
