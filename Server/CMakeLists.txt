cmake_minimum_required(VERSION 3.5.1)
project(Server)

set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
find_package(jsoncpp REQUIRED)


include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${jsoncpp_INCLUDE_DIRS})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")


set(SOURCE_FILES main.cpp containers/synchronizedcontainers/monitor.h Dao.cpp Dao.h dto/LoginRequest.cpp dto/LoginRequest.h entity/Consultation.cpp entity/Consultation.h entity/Account.cpp entity/Account.h entity/enums/AccountRole.h entity/enums/AccountStatus.h entity/enums/ConsultationType.h entity/enums/ConsultationStatus.h ServerSocket.cpp ServerSocket.h containers/synchronizedcontainers/SynchronizedQueue.h containers/OutgoingMessage.cpp containers/OutgoingMessage.h dto/DailyConsultationsListResponse.cpp dto/DailyConsultationsListResponse.h serialization/Serializer.cpp serialization/Serializer.h serialization/Serializable.h serialization/Deserializer.cpp serialization/Deserializer.h dto/enums/StatusType.h dto/LoginResponse.cpp dto/LoginResponse.h threads/TCPThread.cpp threads/TCPThread.h threads/Thread.cpp threads/Thread.h ClientMessageBuilder.cpp ClientMessageBuilder.h Message.cpp Message.h containers/synchronizedcontainers/MutualExclusiveHashMap.h threads/ClientLogic.cpp threads/ClientLogic.h dto/RegistrationRequest.cpp dto/RegistrationRequest.h dto/RegistrationResponse.cpp dto/RegistrationResponse.h threads/MessageSender.cpp threads/MessageSender.h MongoInstanceContainer.cpp MongoInstanceContainer.h dto/DailyConsultationsListRequest.cpp dto/DailyConsultationsListRequest.h dto/NewConsultationRequest.cpp dto/NewConsultationRequest.h dto/NewConsultationResponse.cpp dto/NewConsultationResponse.h entity/ConsultationInfoForClient.cpp entity/ConsultationInfoForClient.h entity/AccountInfoForClient.cpp entity/AccountInfoForClient.h dto/Request.cpp dto/Request.h Client.cpp Client.h threads/ClientInOutAction.cpp threads/ClientInOutAction.h dto/ReservationRequest.cpp dto/ReservationRequest.h dto/ReservationResponse.cpp dto/ReservationResponse.h dto/UsersConsultationsRequest.cpp dto/UsersConsultationsRequest.h dto/UsersConsultationsResponse.cpp dto/UsersConsultationsResponse.h dto/CancelConsultationRequest.cpp dto/CancelConsultationRequest.h dto/CancelConsultationResponse.cpp dto/CancelConsultationResponse.h Context.cpp Context.h dto/InactiveUsersRequest.cpp dto/InactiveUsersRequest.h dto/InactiveUsersResponse.cpp dto/InactiveUsersResponse.h dto/AcceptAccountsRequest.cpp dto/AcceptAccountsRequest.h dto/AcceptAccountsResponse.cpp dto/AcceptAccountsResponse.h dto/RejectAccountsRequest.cpp dto/RejectAccountsRequest.h dto/RejectAccountsResponse.cpp dto/RejectAccountsResponse.h dto/AcceptConsultationRequest.cpp dto/AcceptConsultationRequest.h dto/RejectConsultationRequest.cpp dto/RejectConsultationRequest.h dto/AcceptConsultationResponse.cpp dto/AcceptConsultationResponse.h dto/RejectConsultationResponse.cpp dto/RejectConsultationResponse.h)



add_executable(Server ${SOURCE_FILES})

target_compile_options(Server PRIVATE -ljsoncpp)
target_link_libraries(Server jsoncpp)
target_link_libraries(Server ${jsoncpp_LIBRARIES})
target_link_libraries(Server Threads::Threads)
target_link_libraries(Server ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(Server ${LIBBSONCXX_LIBRARIES})