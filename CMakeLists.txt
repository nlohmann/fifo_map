
cmake_minimum_required(VERSION 3.16)

project("nlohmann-fifo-map"
    VERSION 1.0.0
    LANGUAGES CXX
)

include(GNUInstallDirs)

add_library("nlohmann-fifo-map" INTERFACE)
add_library("nlohmann-fifo-map::nlohmann-fifo-map" ALIAS "nlohmann-fifo-map")
add_library("fifo_map::fifo_map" ALIAS "nlohmann-fifo-map") #Only for backward comptability
target_include_directories("nlohmann-fifo-map" INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


add_executable("unit"
    "test/unit.cpp"
)
target_include_directories("unit" PRIVATE "test/thirdparty")
target_link_libraries("unit" PRIVATE "nlohmann-fifo-map::nlohmann-fifo-map")


