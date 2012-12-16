# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise7)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(filter7       filter.cxx       )

TARGET_LINK_LIBRARIES(filter7       ${ITK_LIBRARIES} )
