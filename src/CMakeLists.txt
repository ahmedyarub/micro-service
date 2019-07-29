cmake_minimum_required(VERSION 3.14.5)

project(micro-service)

find_package(unofficial-http-parser REQUIRED)

find_package(fmt CONFIG REQUIRED)

find_package(unofficial-http-parser REQUIRED)

find_path(CLARA_INCLUDE_DIR include/clara.hpp)
if (CLARA_INCLUDE_DIR STREQUAL "CLARA_INCLUDE_DIR-NOTFOUND")
    message(FATAL_ERROR "Could not find Clara.")
endif ()
include_directories(${CLARA_INCLUDE_DIR})

find_package(restinio REQUIRED)

set(LIB_SUFFIX "64")
if (WIN32)
    set(SOCI_LIBS SOCI::soci_core_static SOCI::soci_sqlite3_static)
    ADD_DEFINITIONS(-D_WIN32_WINDOWS)
    ADD_DEFINITIONS(-D_WINSOCK_DEPRECATED_NO_WARNINGS)
    ADD_DEFINITIONS(-D_HAS_STD_BYTE=0)
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
    set(SOCI_INCLUDE_DIR "C:/Program Files (x86)/SOCI/include")
else ()
    set(SOCI_LIBS SOCI::soci_core SOCI::soci_sqlite3)
    set(CMAKE_MODULE_PATH "/usr/cmake")
endif ()

find_package(Soci REQUIRED COMPONENTS sqlite3 CONFIGS "SOCI.cmake")

find_package(json-dto CONFIG REQUIRED)

set(OPENSSL_VERSION "1.0.1")

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
ADD_DEFINITIONS(-D_TURN_OFF_PLATFORM_STRING=OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME}
        main.cpp
        microsvc_controller.cpp
        foundation/basic_controller.cpp
        cache/redis_cache.cpp
        )

set(MICROSERVICE_INCLUDE_DIR "foundation/include")

include_directories(${MICROSERVICE_INCLUDE_DIR})
include_directories(${SOCI_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}
        restinio::restinio
        ${SOCI_LIBS}
        fmt::fmt
        fmt::fmt-header-only
        cpp_redis
        tacopie
        json-dto::json-dto
        )