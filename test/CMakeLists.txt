cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

enable_testing()

FILE(GLOB TEST_SOURCES test.cpp */*.cpp)
message("Test sources are " "${TEST_SOURCES}")

add_executable(unit_tests "${TEST_SOURCES}" "${LIBRARY__SOURCES}" )

target_link_libraries( unit_tests
	gtest
	pthread
	${PROJECT}
)

add_test(test unit_tests)
