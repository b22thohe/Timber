cmake_minimum_required(VERSION 3.10)
project(Timber)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2 COMPONENTS audio graphics window system REQUIRED)

add_executable(Timber Timber.cpp
        Cloud.hpp
        Cloud.cpp)

target_link_libraries(Timber sfml-audio sfml-graphics sfml-window sfml-system)

if(WIN32)
    # Point this to your actual SFML bin path
    set(SFML_BIN_DIR "C:/SFML/bin")

    add_custom_command(TARGET Timber POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_BIN_DIR}/sfml-audio-2.dll"
            "${SFML_BIN_DIR}/sfml-audio-d-2.dll"
            "${SFML_BIN_DIR}/sfml-graphics-2.dll"
            "${SFML_BIN_DIR}/sfml-graphics-d-2.dll"
            "${SFML_BIN_DIR}/sfml-window-2.dll"
            "${SFML_BIN_DIR}/sfml-window-d-2.dll"
            "${SFML_BIN_DIR}/sfml-system-2.dll"
            "${SFML_BIN_DIR}/sfml-system-d-2.dll"
            # Keep openal32.dll if you have it, as it's required for audio
            "${SFML_BIN_DIR}/openal32.dll"
            "$<TARGET_FILE_DIR:Timber>"
    )
endif()

add_custom_command(TARGET Timber POST_BUILD
    # Copy graphics folder
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/graphics"
    "$<TARGET_FILE_DIR:Timber>/graphics"

    # Copy fonts folder
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/fonts"
    "$<TARGET_FILE_DIR:Timber>/fonts"

    # Copy fonts folder
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/sound"
    "$<TARGET_FILE_DIR:Timber>/sound"
)