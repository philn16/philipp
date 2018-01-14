cmake_minimum_required(VERSION 3.0)

#project(philppTests)

#add_subdirectory(gtest)
#add_subdirectory(gmock)

#target_include_directories(philppTests
    #PUBLIC ${PROJECT_SOURCE_DIR}/include
#)

#FILE(GLOB SRCS *.cpp)
#FILE(GLOB SRCS *.cpp ${dsd_SOURCE_DIR}/src/*.cpp)


#add_custom_target(test
    #DEPENDS unit_tests
    #COMMAND unit_tests
#)

#ADD_EXECUTABLE(dsdtest ${SRCS})
#TARGET_LINK_LIBRARIES(dsdtest gtest)

enable_testing()

set(binary_SOURCES ${PROJECT_SOURCE_DIR}/*)

add_executable(unit_tests test.cpp /home/phil/git/phil++/src/someFile.cpp )

target_link_libraries( unit_tests
	gtest
	pthread
	${PROJECT}
)

#target_link_libraries( testExe PRIVATE ${PROJECT} )

add_test(test_all unit_tests)

message( ${binary_SOURCES} )
