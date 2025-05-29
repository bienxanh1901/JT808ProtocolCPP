enable_testing()

file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cpp")

add_executable(
  JT808ProtocolTest
  ${HEADERS}
  ${SOURCES}
)

target_link_libraries(
  JT808ProtocolTest
  GTest::gtest_main
  JT808Protocol
  nlohmann_json_schema_validator
)

include(GoogleTest)
gtest_discover_tests(JT808ProtocolTest)
