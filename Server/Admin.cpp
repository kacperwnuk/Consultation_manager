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
                disconnectAll();
                int newPort;
                std::cin>>newPort;
                tcpThread->changePort(newPort);
                break;
            case restartCommand:
                cout << "Restarting server..." << endl;
                disconnectAll();
                tcpThread->shutdownPort();
                tcpThread->cancel();
                running = false;
                toRet = 42;
                sleep(5);
                break;
            case sendToCommand:
                break;
            case seelogged:
                printLogged();
                break;
            case seeusers:
                printUsers();
                break;
            case disconnect:
                handleDisconnect();
                break;
            case resetPassword:
                changePass();
                break;
            case deleteAccount:
                deleteAcc();
                break;
            default:
                std::cout<<"niepoprawna komenda"<<std::endl;
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
    mapStringCommands["seelogged"] = seelogged;
    mapStringCommands["seeusers"] = seeusers;
    mapStringCommands["disconnect"] = disconnect;
    mapStringCommands["resetpassword"] = resetPassword;
    mapStringCommands["deleteaccount"] = deleteAccount;
}

void Admin::printLogged(){
    auto clients = tcpThread->getClients();
    int i = 0;
    for (auto client : clients){
        std::cout<<i<<"\t"<<client->getLogic().getContext().getLogin()<<std::endl;
        ++i;
    }
}

void Admin::printUsers(){
    auto dao = Dao::getDaoCollection("TIN", "account");
    auto clients = dao->getAllAccounts();
    int i = 0;
    for (auto client : clients){
        std::cout<<i<<"\t"<<" login: "<<client.getLogin()<<" "<<client<<std::endl;
        ++i;
    }
}

void Admin::handleDisconnect(){
    std::string command;
    std::cin>>command;
    if (command == "all"){
        disconnectAll();
        return;
    }
    try{
        int index = std::stoi(command);
        int max_ind = tcpThread->getClients().size()-1;
        if (index<0 || index > max_ind){
            std::cout<<"index poza zakresem"<<std::endl;
            return;
        }
        disconnectOne(index);
    }
    catch(std::exception e){
        e.what();
    }
}
void Admin::disconnectAll() {
    while (tcpThread->getClients().size() > 0) {
        disconnectOne(0);
    }
    tcpThread->disconnectUsers();
}
void Admin::disconnectOne(int index){
    tcpThread->getClients()[index]->disconnect();
    tcpThread->disconnectUsers();

}

void Admin::changePass(){
    std::string newPass;
    int user_index;
    std::cin>>user_index;
    std::cin>>newPass;
    auto dao = Dao::getDaoCollection("TIN", "account");
    auto clients = dao->getAllAccounts();
    int max_ind = clients.size()-1;
    if (user_index<0 || user_index > max_ind){
        std::cout<<"index poza zakresem"<<std::endl;
        return;
    }
    Account client = clients[user_index];
    Account newClient(client.getDocumentFormat());
    newClient.setPasswordHash(newPass);
    dao->updateDocument(client.getDocumentFormat(), newClient.getDocumentFormat());
    std::cout<<"zmieniono haslo uzytkownika: "<<client.getLogin()<<std::endl;
}

void Admin::deleteAcc(){
    int user_index;
    std::cin>>user_index;

    auto dao = Dao::getDaoCollection("TIN", "account");
    auto clients = dao->getAllAccounts();
    int max_ind = clients.size()-1;
    if (user_index<0 || user_index > max_ind){
        std::cout<<"index poza zakresem"<<std::endl;
        return;
    }
    Account client = clients[user_index];

    dao->deleteDocument(client.getDocumentFormat());
    std::cout<<"usunieto uzytkownika: "<<client.getLogin()<<std::endl;
}