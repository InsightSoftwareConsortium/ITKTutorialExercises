# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise6)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(filter6       filter.cxx       )
ADD_EXECUTABLE(filter6Answer filterAnswer.cxx )

TARGET_LINK_LIBRARIES(filter6       ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES(filter6Answer ${ITK_LIBRARIES} )
