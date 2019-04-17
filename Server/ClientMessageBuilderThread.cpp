//
// Created by kacper on 17.04.2019.
//

#include "ClientMessageBuilderThread.h"

void ClientMessageBuilderThread::run() {
    readDemands.put(socket, demand);
    auto messageSize = 0;
    auto isRunning = true;
    while(isRunning){
        pthread_mutex_lock(&mutex);
        if (size < demand) {
            pthread_cond_wait(&readComplete, &mutex);
        }
        if(!duringBuilding) {
            demand = atoi(header);
            payload = new char[demand];
            readDemands.put(socket, demand);
            duringBuilding = true;
            std::cout << "header" << readDemands.get(socket) << " " << demand << std::endl;
            size = 0;
        } else {
            std::cout << "payload" << payload << std::endl;
            delete[] payload;
            demand = 4;
            readDemands.put(socket, demand);
            duringBuilding = false;
            size = 0;
        }
        pthread_mutex_unlock(&mutex);
    }
}

ClientMessageBuilderThread::ClientMessageBuilderThread(int socket, std::shared_ptr<SynchronizedQueue<IncomingMessage>> clientMessageBuffer,
                                                       MutualExclusiveHashMap<size_t> &readDemands): readDemands(readDemands) {
    this->socket = socket;
//    this->messageBuffer = clientMessageBuffer;
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&readComplete, nullptr);
    size = 0;
}