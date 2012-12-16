# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise22)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(registration22       registration.cxx       )

TARGET_LINK_LIBRARIES(registration22       ${ITK_LIBRARIES} )
