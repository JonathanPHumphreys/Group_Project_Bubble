project(Bubble)
cmake_minimum_required(VERSION 3.0)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

ADD_EXECUTABLE(Bubble src/main.cpp src/constants.h src/graphics.h src/graphics.cpp src/UI.h src/UI.cpp)
TARGET_LINK_LIBRARIES(Bubble ${CONAN_LIBS})

set (CMAKE_CXX_STANDARD 11)
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "Bubble")

FILE(COPY assets/ DESTINATION bin/assets)

