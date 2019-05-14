//
// Created by Marcin on 14.05.2019.
//

#include "Client.h"

Client::Client(int fd): clientLogic(inQueue, outQueue, readyToSend), clientInOutAction(fd, inQueue, outQueue, readyToSend, readyToReceive) {
    this->fd = fd;
    clientLogic.start();
    clientInOutAction.start();
}

bool Client::isReadyToReceive() {
    return readyToReceive;
}

void Client::stop() {

}

void Client::receive() {
    readyToReceive = false;
    clientInOutAction.receive();
}

void Client::send() {
    readyToReceive = true;
    clientInOutAction.send();
}

bool Client::isReadyToSend() {
    return readyToSend;
}

int Client::getFd() const {
    return fd;
}
