cmake_minimum_required(VERSION 3.16)

project(JT808Protocol LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
)

FetchContent_MakeAvailable(googletest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB HEADERS "include/*/*.h" "include/*/*/*.h" "include/*/*/*/*.h")
file(GLOB SOURCES "src/*.cpp")

add_library(${CMAKE_PROJECT_NAME} ${HEADERS} ${SOURCES})

add_subdirectory(test)

include(GNUInstallDirs)
install(TARGETS ${CMAKE_PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
