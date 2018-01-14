cmake_minimum_required(VERSION 3.0)

enable_testing()

add_executable(unit_tests test.cpp "${library_SOURCES}" )

target_link_libraries( unit_tests
	gtest
	pthread
	${PROJECT}
)

#target_link_libraries( testExe PRIVATE ${PROJECT} )

add_test(test unit_tests)

