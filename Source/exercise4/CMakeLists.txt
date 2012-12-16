# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise4)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(filter4       filter.cxx       )
ADD_EXECUTABLE(filter4Answer filterAnswer.cxx )

TARGET_LINK_LIBRARIES(filter4       ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES(filter4Answer ${ITK_LIBRARIES} )
