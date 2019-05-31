cmake_minimum_required(VERSION 3.6)

project(micro-service)

if (COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif (COMMAND cmake_policy)

if (POLICY CMP0012)
    CMAKE_POLICY(SET CMP0012 NEW)
endif ()

find_package(unofficial-http-parser REQUIRED)

find_package(fmt CONFIG REQUIRED)

find_path(CLARA_INCLUDE_DIR include/clara.hpp)
if (CLARA_INCLUDE_DIR STREQUAL "CLARA_INCLUDE_DIR-NOTFOUND")
    message(FATAL_ERROR "Could not find Clara.")
endif ()
include_directories(${CLARA_INCLUDE_DIR})

find_package(restinio REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(cpp-redis REQUIRED)

set(LIB_SUFFIX "64")
find_package(Soci REQUIRED COMPONENTS sqlite3 CONFIGS "SOCI.cmake")
if (WIN32)
    set(SOCI_LIBS SOCI::soci_core_static SOCI::soci_sqlite3_static)
else ()
    set(SOCI_LIBS SOCI::soci_core SOCI::soci_sqlite3)
endif ()

set(OPENSSL_VERSION "1.0.1")

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
ADD_DEFINITIONS(-D_WIN32_WINDOWS)
ADD_DEFINITIONS(-D_TURN_OFF_PLATFORM_STRING=OFF)
ADD_DEFINITIONS(-D_WINSOCK_DEPRECATED_NO_WARNINGS)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME}
        main.cpp
        #        main.cpp
        #        microsvc_controller.cpp
        #        foundation/network_utils.cpp
        #        foundation/basic_controller.cpp
        #        cache/redis_cache.cpp
        )

set(MICROSERVICE_INCLUDE_DIR "foundation/include")
set(SOCI_INCLUDE_DIR "C:/Program Files/SOCI/include")

include_directories(${MICROSERVICE_INCLUDE_DIR})
include_directories(${SOCI_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}
        restinio::restinio
        ${SOCI_LIBS}
        fmt::fmt
        fmt::fmt-header-only
        cpp_redis
        tacopie
        )