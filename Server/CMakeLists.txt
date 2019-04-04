cmake_minimum_required(VERSION 3.5.1)
project(Server)

set(CMAKE_CXX_STANDARD 11)

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


set(SOURCE_FILES main.cpp monitor.h Dao.cpp Dao.h dto/LoginRequest.cpp dto/LoginRequest.h entity/Consultation.cpp entity/Consultation.h entity/Account.cpp entity/Account.h entity/enums/AccountRole.h entity/enums/AccountStatus.h entity/enums/ConsultationType.h entity/enums/ConsultationStatus.h ServerSocket.cpp ServerSocket.h containers/SynchronizedVector.cpp containers/SynchronizedVector.h containers/ThreadArgs.cpp containers/ThreadArgs.h containers/SynchronizedQueue.cpp containers/SynchronizedQueue.h)



add_executable(Server ${SOURCE_FILES})

target_compile_options(Server PRIVATE -ljsoncpp)
target_link_libraries(Server jsoncpp)
target_link_libraries(Server ${jsoncpp_LIBRARIES})
target_link_libraries(Server Threads::Threads)
target_link_libraries(Server ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(Server ${LIBBSONCXX_LIBRARIES})