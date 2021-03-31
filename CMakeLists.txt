cmake_minimum_required(VERSION 2.8)

project(fifo_map LANGUAGES CXX)

add_executable(unit
    src/fifo_map.hpp test/thirdparty/catch/catch.hpp test/unit.cpp
)

target_include_directories(unit PRIVATE "test" "src" "test/thirdparty")

if(MSVC)
    set(CMAKE_CXX_FLAGS
        "/EHsc"
    )

    STRING(REPLACE "/O2" "/Od" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})

    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
else(MSVC)
    set(CMAKE_CXX_FLAGS
        "-std=c++11"
    )
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif()
endif(MSVC)

include_directories(
    src test
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/>
)
