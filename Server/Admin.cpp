//
// Created by slawek on 01.06.19.
//

#include "Admin.h"

Admin::Admin(TCPThread* thread){
    this->tcpThread = thread;
}

int Admin::run(){
    initialize();

    char value[256];
    int toRet;
    while (running) {
        string message;
        cin >> value;
        switch (mapStringCommands[value]) {
            case stopCommand:
                cout << "Stopping server..." << endl;
                tcpThread->cancel();
                running = false;
                toRet = 0;
                break;
            case changePortCommand:
                std::cout<<"changing port"<<std::endl;
                tcpThread->changePort(9998);
                break;
            case restartCommand:
                cout << "Restarting server..." << endl;
                //tcpThread->cancel();
                running = false;
                toRet = 42;
                break;
            case sendToCommand:
                break;
            default:
                break;
        }
    }
    return toRet;
}
void Admin::initialize() {
    running = true;
    mapStringCommands["stop"] = stopCommand;
    mapStringCommands["restart"] = restartCommand;
    mapStringCommands["changeport"] = changePortCommand;
    mapStringCommands["sendto"] = sendToCommand;
}