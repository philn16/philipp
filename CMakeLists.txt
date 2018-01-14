cmake_minimum_required(VERSION 3.0)

set(PROJECT	philipp)

project(${PROJECT})

############################################################
# Create a library
############################################################

# Source files to be used in the library
set(library_SOURCES
    src/main.cpp
    src/someFile.cpp
)

#Generate the shared library from the library sources
add_library(${PROJECT} SHARED ${library_SOURCES})


target_include_directories(${PROJECT}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

############################################################
# Create an executable
############################################################

# Source fles for the binary
set(binary_SOURCES
    src/main.cpp
    src/someFile.cpp
)

# Add an executable with the above sources
add_executable(testExe ${binary_SOURCES})

# link the new hello_library target with the hello_binary target
target_link_libraries( testExe
    PRIVATE ${PROJECT}
)

############################################################
# Install
############################################################

# Binaries
install (TARGETS testExe
    DESTINATION bin)

# Library
# Note: may not work on windows
install (TARGETS ${PROJECT}
    LIBRARY DESTINATION lib)


# Config
install (FILES cmake-examples.conf
    DESTINATION etc)


FILE(GLOB HEADERS include/*.h include/*.hpp)

#set( CMAKE_INSTALL_LIBDIR  include)
message("installing " ${HEADERS}  )
message("project is  " ${PROJECT} )
install( FILES ${HEADERS} DESTINATION include/philipp)

#install( HEADERS ${CMAKE_INSTALL_LIBDIR} )
