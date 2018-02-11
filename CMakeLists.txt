cmake_minimum_required(VERSION 3.0)

set(PROJECT	philipp)

project(${PROJECT})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
############################################################
# Create a library
############################################################

FILE(GLOB SOURCES src/*)
message("sources are " "${SOURCES}" )

FILE(GLOB HEADERS include/*.h include/*.hpp include/*/*.hpp)
message("headers are " "${HEADERS}" )

# Source files to be used in the library
#set(SOURCES ${SOURCE} )

#Generate the shared library from the library sources
add_library(${PROJECT} SHARED ${SOURCES})

target_include_directories( ${PROJECT} PUBLIC ${PROJECT_SOURCE_DIR}/include )

############################################################
# Create an executable
############################################################

# Source fles for the binary
set(binary_SOURCES mains/main.cpp src/someFile.cpp )

# Add an executable with the above sources
add_executable(philExe ${binary_SOURCES})

# link the new hello_library target with the hello_binary target
target_link_libraries( philExe PRIVATE ${PROJECT} )

############################################################
# Install
############################################################

# Binaries
install (TARGETS philExe DESTINATION bin)

# Library
install (TARGETS ${PROJECT} LIBRARY DESTINATION lib)

# Config
#install (FILES cmake-examples.conf DESTINATION etc)

# headers

install( FILES ${HEADERS} DESTINATION include/philipp)


############################################################
# tesets
############################################################

add_subdirectory(test)

