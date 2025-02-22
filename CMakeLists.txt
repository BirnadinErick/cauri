cmake_minimum_required(VERSION 3.16)
project(cauri LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include(FetchContent)

FetchContent_Declare(
        webview
        GIT_REPOSITORY https://github.com/webview/webview
        GIT_TAG 0.12.0)
FetchContent_MakeAvailable(webview)

# embed views
set(VIEWS_DIR "${CMAKE_SOURCE_DIR}/views")
set(OUTPUT_HEADER "${CMAKE_BINARY_DIR}/views.h")

file(GLOB VIEW_FILES "${VIEWS_DIR}/*.html")

file(WRITE ${OUTPUT_HEADER} "#pragma once\n\n")

foreach (FILE ${VIEW_FILES})
    get_filename_component(VIEW_NAME ${FILE} NAME_WE)  # Extract filename without extension

    file(READ ${FILE} VIEW_CONTENT)

    string(REPLACE "-" "_" VIEW_NAME ${VIEW_NAME})
    string(REPLACE ")\"html" ")\\\"html" VIEW_CONTENT "${VIEW_CONTENT}")

    file(APPEND ${OUTPUT_HEADER} "constexpr const char ${VIEW_NAME}[] = R\"html(${VIEW_CONTENT})html\";\n\n")
endforeach ()

add_executable(cauri WIN32)
target_sources(cauri PRIVATE ${PROJECT_SOURCE_DIR}/main.cpp)
target_include_directories(cauri PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(cauri PRIVATE webview::core)