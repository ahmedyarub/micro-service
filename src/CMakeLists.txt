cmake_minimum_required(VERSION 3.0)

project(micro-service)

if (POLICY CMP0012)
    CMAKE_POLICY(SET CMP0012 NEW)
endif ()

find_package(cpprestsdk REQUIRED PATHS "/usr/lib/x86_64-linux-gnu/cmake/")
find_package(Boost REQUIRED COMPONENTS random system thread filesystem chrono atomic date_time regex)
find_package(OpenSSL 1.0.1 REQUIRED)

set(LIB_SUFFIX "64")
find_package(Soci REQUIRED COMPONENTS sqlite3 CONFIGS "SOCI.cmake")

set(OPENSSL_VERSION "1.0.1")

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
ADD_DEFINITIONS(-D_WIN32_WINDOWS)
ADD_DEFINITIONS(-D_TURN_OFF_PLATFORM_STRING=OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cpp
        microsvc_controller.cpp
        foundation/network_utils.cpp
        foundation/basic_controller.cpp)

set(MICROSERVICE_INCLUDE_DIR "foundation/include")
set(SOCI_INCLUDE_DIR "C:/Program Files (x86)/SOCI/include")

include_directories(${MICROSERVICE_INCLUDE_DIR})
include_directories(${SOCI_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}
        cpprestsdk::cpprest
        Boost::boost
        Boost::random
        Boost::system
        Boost::thread
        Boost::filesystem
        Boost::chrono
        Boost::atomic
        Boost::date_time
        Boost::regex
        OpenSSL::SSL
        SOCI::soci_core
        SOCI::soci_sqlite3
        )