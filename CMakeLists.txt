
cmake_minimum_required(VERSION 3.16)

project("nlohmann-fifo-map"
    VERSION 1.0.0
    LANGUAGES CXX
)

include(GNUInstallDirs)

add_library("nlohmann-fifo-map" INTERFACE)
add_library("nlohmann-fifo-map::nlohmann-fifo-map" ALIAS "nlohmann-fifo-map")
add_library("fifo_map::fifo_map" ALIAS "nlohmann-fifo-map") #For backward comptability
target_include_directories("nlohmann-fifo-map" INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


add_executable("unit"
    "test/unit.cpp"
)
target_include_directories("unit" PRIVATE "test/thirdparty")
target_link_libraries("unit" PRIVATE "nlohmann-fifo-map::nlohmann-fifo-map")



install(TARGETS "nlohmann-fifo-map"
    EXPORT "nlohmann-fifo-map-target"
)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
if(NOT TARGET "uninstall")
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY
    )
    add_custom_target("uninstall"
        COMMAND "${CMAKE_COMMAND}" "-P" "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    )
endif()

include(CMakePackageConfigHelpers)
install(EXPORT "nlohmann-fifo-map-target"
    DESTINATION "share/nlohmann-fifo-map"
    NAMESPACE "nlohmann-fifo-map::"
)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/nlohmann-fifo-map-config.cmake"
    INSTALL_DESTINATION "share/nlohmann-fifo-map"
)
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/nlohmann-fifo-map-config-version.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/nlohmann-fifo-map-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/nlohmann-fifo-map-config-version.cmake"
    DESTINATION "share/nlohmann-fifo-map"
)
