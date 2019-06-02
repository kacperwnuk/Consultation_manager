#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <cstring>
//#include <zconf.h>
#include <pthread.h>
#include <vector>
#include <poll.h>
#include <climits>
#include <map>
#include <bsoncxx/builder/stream/document.hpp>
#include "ServerSocket.h"
#include "containers/synchronizedcontainers/SynchronizedVector.h"
#include "Dao.h"
#include "entity/Account.h"
#include "entity/Consultation.h"
#include "containers/OutgoingMessage.h"
#include "containers/synchronizedcontainers/SynchronizedQueue.h"
#include "serialization/Serializer.h"
#include "dto/DailyConsultationsListResponse.h"
#include "serialization/Deserializer.h"
#include "dto/enums/StatusType.h"
#include "dto/LoginResponse.h"
#include "threads/TCPThread.h"
#include "threads/MessageSender.h"
#include "Admin.h"
#include <jsoncpp/json/json.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
using namespace std;

in_port_t getPortFromArgument(char *arg) {
    in_port_t port;
    char *endPtr = nullptr;
    errno = 0;
    auto argumentPort = strtoul(arg, &endPtr, 10);
    if (arg == endPtr) {
        throw invalid_argument("port invalid: no digits found");
    } else if (errno == ERANGE && argumentPort == LONG_MIN) {
        throw invalid_argument("port invalid: underflow occurred");
    } else if (errno == ERANGE && argumentPort == LONG_MAX) {
        throw invalid_argument("port invalid: overflow occurred");
    } else if (errno == EINVAL) {
        throw invalid_argument("port invalid: base contains unsupported value");
    } else if (errno != 0 && argumentPort == 0) {
        throw invalid_argument("port invalid: unspecified error occurred");
    } else if (errno == 0 && arg) {
        if (argumentPort < USHRT_MAX) {
            port = static_cast<in_port_t>(argumentPort);
        } else {
            throw invalid_argument("port invalid: port number too big");
        }
    } else {
        throw invalid_argument("port invalid: dunno");
    }
    return port;
}

int main(int argc, char *argv[]) {
    in_port_t port = 9999; // default port
    if (argc > 1) {
        try {
            port = getPortFromArgument(argv[1]);
            cout << "starting on port: " << port << endl;
        } catch (invalid_argument &e) {
            cout << e.what() << endl << "starting on default port(" << port << ")" << endl;
        }
    }

    TCPThread tcpThread(port);
    tcpThread.start();

    Admin admin(&tcpThread);
    int result = admin.run();

    tcpThread.join();
    cout << "Server stopped." << endl;
    if (result == 42) {

        tcpThread.cancel();
        execve(argv[0], argv, NULL);
    }
    else
        return 0;
}


#pragma clang diagnostic pop