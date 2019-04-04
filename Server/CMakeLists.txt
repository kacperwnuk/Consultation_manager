cmake_minimum_required(VERSION 3.5.1)
project(Server)

set(CMAKE_CXX_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCE_FILES main.cpp monitor.h dto/LoginRequest.cpp dto/LoginRequest.h entity/Consultation.cpp entity/Consultation.h entity/Account.cpp entity/Account.h entity/enums/AccountRole.h entity/enums/AccountStatus.h entity/enums/ConsultationType.h entity/enums/ConsultationStatus.h ServerSocket.cpp ServerSocket.h containers/SynchronizedVector.cpp containers/SynchronizedVector.h containers/ThreadArgs.cpp containers/ThreadArgs.h containers/SynchronizedQueue.cpp containers/SynchronizedQueue.h)

add_executable(Server ${SOURCE_FILES})

target_link_libraries(Server Threads::Threads)