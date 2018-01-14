cmake_minimum_required(VERSION 3.0)

set(PROJECT	philipp)

project(${PROJECT})

############################################################
# Create a library
############################################################

# Source files to be used in the library
set(library_SOURCES src/someFile.cpp )

#Generate the shared library from the library sources
add_library(${PROJECT} SHARED ${library_SOURCES})

target_include_directories( ${PROJECT} PUBLIC ${PROJECT_SOURCE_DIR}/include )

############################################################
# Create an executable
############################################################

# Source fles for the binary
set(binary_SOURCES mains/main.cpp src/someFile.cpp )

# Add an executable with the above sources
add_executable(testExe ${binary_SOURCES})

# link the new hello_library target with the hello_binary target
target_link_libraries( testExe PRIVATE ${PROJECT} )

############################################################
# Install
############################################################

# Binaries
install (TARGETS testExe DESTINATION bin)

# Library
install (TARGETS ${PROJECT} LIBRARY DESTINATION lib)

# Config
#install (FILES cmake-examples.conf DESTINATION etc)

# headers
FILE(GLOB HEADERS include/*.h include/*.hpp)
install( FILES ${HEADERS} DESTINATION include/philipp)


############################################################
# tesets
############################################################

add_subdirectory(test)

