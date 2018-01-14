cmake_minimum_required(VERSION 3.0)

project(dsdtest)

#add_subdirectory(gtest)
#add_subdirectory(gmock)

FILE(GLOB SRCS *.cpp)


#add_custom_target(test
    #DEPENDS dsdtest
    #COMMAND dsdtest
#)

#ADD_EXECUTABLE(dsdtest ${SRCS})
#TARGET_LINK_LIBRARIES(dsdtest gtest)

enable_testing()

add_executable(unit_tests test.cpp)

target_link_libraries( unit_tests
	gtest
	pthread
)

add_test(test_all unit_tests)
