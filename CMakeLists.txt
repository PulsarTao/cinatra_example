cmake_minimum_required(VERSION 3.7)
project(cinatra_example)

set(CMAKE_CXX_STANDARD 11)

find_package(cinatra REQUIRED)
include_directories(${cinatra_INCLUDES})

find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(OpenSSL REQUIRED)

include_directories(
        ${Boost_INCLUDE_DIR}
        ${OPENSSL_INCLUDE_DIR})

if (WIN32)
    set(EXTRA_LIB mswsock ws2_32)
endif ()

macro(add_example name)
    add_executable(${name} ${name}/main.cpp)

    target_link_libraries(${name}
            ${cinatra_LIBRARIES}
            ${Boost_LIBRARIES}
            ${OPENSSL_LIBRARIES}
            ${CMAKE_THREAD_LIBS_INIT}
            ${EXTRA_LIB})
endmacro()


add_example(cinatra_http_example)
add_example(https_server)

