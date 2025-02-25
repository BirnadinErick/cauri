cmake_minimum_required(VERSION 3.16)
project(cauri LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

find_package(Threads REQUIRED)
include(FetchContent)

FetchContent_Declare(
        webview
        GIT_REPOSITORY https://github.com/webview/webview
        GIT_TAG 0.12.0)
FetchContent_MakeAvailable(webview)

add_executable(cauri WIN32)
target_sources(cauri PRIVATE ${PROJECT_SOURCE_DIR}/main.c ${PROJECT_SOURCE_DIR}/cJSON/cJSON.c ${PROJECT_SOURCE_DIR}/views.c)
target_link_libraries(cauri PRIVATE webview::core_static Threads::Threads)
