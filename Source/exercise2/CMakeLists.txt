# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise2)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(myProject2 myProject.cxx )

TARGET_LINK_LIBRARIES(myProject2 ${ITK_LIBRARIES} )
