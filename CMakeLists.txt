cmake_minimum_required(VERSION 2.8)

project(fifo_map LANGUAGES CXX)

add_executable(unit
    src/fifo_map.hpp test/thirdparty/catch/catch.hpp test/unit.cpp
)

if(MSVC)
    set(CMAKE_CXX_FLAGS
        "/EHsc"
    )

    STRING(REPLACE "/O2" "/Od" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})

    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
else(MSVC)
    set(CMAKE_CXX_FLAGS
        "-std=c++11 -stdlib=libc++"
    )
endif(MSVC)

include_directories(
    src test
)
