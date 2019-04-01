cmake_minimum_required(VERSION 3.5.1)
project(Server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp dto/LoginRequest.cpp dto/LoginRequest.h entity/Consultation.cpp entity/Consultation.h entity/Account.cpp entity/Account.h entity/enums/AccountRole.h entity/enums/AccountStatus.h entity/enums/ConsultationType.h entity/enums/ConsultationStatus.h)

add_executable(Server ${SOURCE_FILES})