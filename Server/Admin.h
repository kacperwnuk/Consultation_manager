//
// Created by slawek on 01.06.19.
//

#ifndef SERVER_ADMIN_H
#define SERVER_ADMIN_H

#include <map>
#include <iostream>
#include "threads/TCPThread.h"

using namespace std;
enum Commands {
    stopCommand = 1,
    restartCommand,
    changePortCommand,
    sendToCommand,
    seelogged,
    seeusers,
    disconnect,
    resetPassword,
    deleteAccount
};

class Admin {
    std::map<std::string, Commands> mapStringCommands;
    bool running;
    TCPThread* tcpThread;

    void initialize();
    void printLogged();
    void printUsers();
    void handleDisconnect();
    void disconnectAll();
    void disconnectOne(int);
    void deleteAcc();
    void changePass();
public:
    Admin(TCPThread*);
    int run();

};


#endif //SERVER_ADMIN_H
