cmake_minimum_required(VERSION 3.24)

project(JT808Protocol LANGUAGES CXX)

option(JT808_TEST "Build unit tests" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (JT808_TEST)
  message("Fetching google test")
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
  )
  FetchContent_MakeAvailable(googletest)
endif(JT808_TEST)



include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB HEADERS "include/*/*.h" "include/*/*/*.h" "include/*/*/*/*.h")
file(GLOB SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

if (JT808_TEST)
  message("Configure Unit tests")
  enable_testing()
  add_subdirectory(tests)
endif(JT808_TEST)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
