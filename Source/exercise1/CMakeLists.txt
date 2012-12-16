# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise1)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(HelloWorld1 HelloWorld.cxx )

TARGET_LINK_LIBRARIES(HelloWorld1 ${ITK_LIBRARIES})
