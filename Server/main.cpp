#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <cstring>
#include <zconf.h>
#include <pthread.h>
#include <vector>
#include <poll.h>
#include <map>
#include <bsoncxx/builder/stream/document.hpp>
#include "ServerSocket.h"
#include "containers/SynchronizedVector.h"
#include "containers/ThreadArgs.h"
#include "Dao.h"
#include "entity/Account.h"
#include "entity/Consultation.h"
#include "containers/OutgoingMessage.h"
#include "containers/SynchronizedQueue.h"
#include "containers/OutThreadArgs.h"
#include "containers/DataHandlerThreadArgs.h"
#include <jsoncpp/json/json.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
using namespace std;

enum StringValue {
    stopCommand,
    restartCommand
};
map<string, StringValue> s_mapStringValues;

void initialize() {
    s_mapStringValues["stop"] = stopCommand;
    s_mapStringValues["restart"] = restartCommand;
}

//constexpr unsigned int hash(const char *str, int h = 0) {
//    return !str[h] ? 5381 : (::hash(str, h + 1) * 33) ^ str[h];
//}

void *responseHandler(void *args) {
    auto *threadArgs = static_cast<OutThreadArgs *>(args);
    auto &messages = threadArgs->messages;
    auto &stopCond = threadArgs->stopCond;
    while (stopCond) {
        auto message = messages.get();
        cout << message.payload << endl;
        write(message.fd, message.payload, (size_t) message.size);
    }
}

void *connectionListener(void *args) {
    auto *threadArgs = static_cast<ThreadArgs *>(args);
    auto &sockets = threadArgs->sockets;
    auto &stopCond = threadArgs->stopCond;
    while (stopCond) {
        ServerSocket serverSocket(9999);
        int clientSocket;
        if ((clientSocket = serverSocket.acceptConnection()) != -1) {
            sockets.put(clientSocket);
        }
    }
    cout << "Listener stopped" << endl;
}

void *dataHandler(void *args) {
    auto *threadArgs = static_cast<DataHandlerThreadArgs *>(args);
    auto &sockets = threadArgs->sockets;
    auto &stopCond = threadArgs->stopCond;
    auto &messages = threadArgs->messages;
    do {
        auto &tmpSockets = sockets.getAll();
        auto numberOfSockets = tmpSockets.size();
        struct pollfd pollList[numberOfSockets];
        for (auto i = 0; i < numberOfSockets; ++i) {
            pollList[i].fd = tmpSockets.at(i);
            pollList[i].events = POLLIN;
        }
        auto retval = poll(pollList, numberOfSockets, 200);
        if (retval < 0) {
            fprintf(stderr, "Error while polling: %s\n", strerror(errno));
            return nullptr;
        }
        for (auto i = 0; i < numberOfSockets; ++i) {
            if (((pollList[i].revents & POLLHUP) == POLLHUP) ||
                ((pollList[i].revents & POLLERR) == POLLERR) ||
                ((pollList[i].revents & POLLNVAL) == POLLNVAL))
                return nullptr;
        }
        for (auto i = 0; i < numberOfSockets; ++i) {
            if ((pollList[i].revents & POLLIN) == POLLIN) {
                char buf[1024];
                ssize_t rval;
                memset(buf, 0, sizeof buf);
                if ((rval = read(pollList[i].fd, buf, 1024)) == -1)
                    perror("reading stream message");
                if (rval == 0) {
                    printf("Ending connection\n");
                    sockets.erase(pollList[i].fd);
                    close(pollList[i].fd);
                } else {
                    printf("%d-->%s\n", pollList[i].fd, buf);
                    messages.put(OutgoingMessage(pollList[i].fd, buf, rval));
                }
                fflush(stdout);
            }
        }
    } while (stopCond);
    cout << "data handler stopped" << endl;
}


void daoSamples(){
    Dao dao = Dao("TIN", "consultation");

    auto collec = dao.getCollection();
    auto consultations = collec.find(bsoncxx::builder::stream::document{} << "room" << "315" << bsoncxx::builder::stream::finalize);

    for(auto& cons : consultations){
        Consultation consultation = Consultation(cons);
        std::chrono::milliseconds time(1000);
        consultation.setConsultationDate(b_date(time));
        cout << consultation.getId().to_string() << " " << consultation.getConsultationDate() << endl;

        auto new_cons = consultation.getDocumentFormat();
        dao.updateDocument(cons, new_cons);
    }

    /*
    auto activeLecturers = dao.getAccountsByStatusAndRole(AccountStatus::ACTIVE, AccountRole::LECTURER);

    for (auto& lecturer : activeLecturers){
        cout << lecturer.getId().to_string() << " " << lecturer.getLogin() << endl;
    }

    auto coll = dao.getCollection();
    auto student_doc = coll.find_one(bsoncxx::builder::stream::document{} << "login" << "lotr" << bsoncxx::builder::stream::finalize);
    auto lecturer_doc = coll.find_one(bsoncxx::builder::stream::document{} << "login" << "waldi" << bsoncxx::builder::stream::finalize);

    Account student = Account((*student_doc).view());
    Account lecturer = Account((*lecturer_doc).view());

    auto time = b_date(std::chrono::system_clock::now());

    Consultation consultation = Consultation(lecturer.getId(), "315", student.getId(), ConsultationStatus::AWAITING_LECTURER_CONFIRMATION, ConsultationType::STUDENT_SUGGESTED, time);
    auto cons_doc = consultation.getDocumentFormat();
    dao.setCollection("consultation");
    dao.insertDocument(cons_doc);
     */
//
//
//    string name = "Waldemar";
//    string email = "mailik@o2.pl";
//    string login = "waldi";
//    string password = "zasx";
//    string surname = "Kowalski";
//    Account account(email, login, password, name, surname, AccountRole(0), AccountStatus(0));
//    auto doc_val = account.getDocumentFormat();
//    dao.insertDocument(doc_val);

//    auto result = dao.coll.find(bsoncxx::builder::stream::document{} << "email" << "email" << bsoncxx::builder::stream::finalize);
//    for (auto doc: result){
//        Account acc = Account(doc);
//        cout << acc.getId().to_string() << acc.getAccountStatus() << " " << acc.getEmailAdress() << endl;
//    }
//    auto doc_val = account.getDocumentFormat();
//    auto result = dao.coll.insert_one(doc_val);
}


int main() {
    SynchronizedQueue<OutgoingMessage> outMessages;
    SynchronizedVector<int> sockets;
    auto listenerRunning = true;
    auto dataHandlerRunning = true;
    auto responseHandlerRunning = true;
    auto running = true;
    ThreadArgs listenerThreadArgs(sockets, listenerRunning);
    DataHandlerThreadArgs dataHandlerThreadArgs(outMessages, sockets, dataHandlerRunning);
    OutThreadArgs outgoingMessagesThreadArgs(outMessages, responseHandlerRunning);
    pthread_t listenerThread, dataHandlerThread, responseHandlerThread;
    pthread_create(&listenerThread, nullptr, connectionListener, &listenerThreadArgs);
    pthread_create(&dataHandlerThread, nullptr, dataHandler, &dataHandlerThreadArgs);
    pthread_create(&responseHandlerThread, nullptr, responseHandler, &outgoingMessagesThreadArgs);
    initialize();
    char value[256];
    while (running) {
        cin >> value;
        switch (s_mapStringValues[value]) {
            case stopCommand:
                listenerRunning = false;
                dataHandlerRunning = false;
                cout << "Stopping" << endl;
                running = false;
                break;
            default:
                break;
        }
    }
    pthread_join(listenerThread, nullptr);
    pthread_join(dataHandlerThread, nullptr);
    pthread_join(responseHandlerThread, nullptr);
    return 0;
}



#pragma clang diagnostic pop