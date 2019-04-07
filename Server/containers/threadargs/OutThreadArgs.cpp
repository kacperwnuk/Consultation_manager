//
// Created by Marcin on 04.04.2019.
//

#include "OutThreadArgs.h"

OutThreadArgs::OutThreadArgs(SynchronizedQueue<OutgoingMessage> &messages, bool &stopCond): messages(messages), StoppableThreadArgs(stopCond) {

}
