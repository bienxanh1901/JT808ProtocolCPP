cmake_minimum_required(VERSION 3.24)

project(JT808Protocol LANGUAGES CXX)

option(JT808_TEST "Build unit tests" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# FetchContent_Declare(
#   json-schema-validator
#   URL https://codeload.github.com/pboettch/json-schema-validator/tar.gz/refs/tags/2.3.0
# )
# FetchContent_MakeAvailable(json-schema-validator)

if (JT808_TEST)
  message("Fetching google test")
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
  )
  FetchContent_MakeAvailable(googletest)
endif(JT808_TEST)

file(GLOB HEADERS "include/*/*.h*" "include/*/*/*.h" "include/*/*/*/*.h")

file(GLOB SOURCES "src/*.cpp")

set(JT808_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${JT808_INCLUDE_DIR})

add_subdirectory(thirdparty)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

if (JT808_TEST)
  message("Configure Unit tests")
  enable_testing()
  add_subdirectory(tests)
endif(JT808_TEST)

target_link_libraries(${PROJECT_NAME} nlohmann_json_schema_validator)

target_include_directories(${PROJECT_NAME} PUBLIC
  "$<BUILD_INTERFACE:${JT808_INCLUDE_DIR}>"
  "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
