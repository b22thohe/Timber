cmake_minimum_required(VERSION 3.10)
project(Timber)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2 COMPONENTS graphics window system REQUIRED)

add_executable(Timber Timber.cpp)

target_link_libraries(Timber sfml-graphics sfml-window sfml-system)

add_custom_command(TARGET Timber POST_BUILD
        # Copy graphics folder
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/graphics"
    "$<TARGET_FILE_DIR:Timber>/graphics"

        # Copy fonts folder
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/fonts"
    "$<TARGET_FILE_DIR:Timber>/fonts"
)