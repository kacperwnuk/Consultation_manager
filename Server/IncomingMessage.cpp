//
// Created by kacper on 17.04.2019.
//

#include "IncomingMessage.h"

IncomingMessage::IncomingMessage(int size, char* payload): size(size), payload(payload) {
}

IncomingMessage::~IncomingMessage() {
}

IncomingMessage::IncomingMessage() {

}
