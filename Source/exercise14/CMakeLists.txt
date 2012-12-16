# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise14)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(filter14       filter.cxx       )

TARGET_LINK_LIBRARIES(filter14       ${ITK_LIBRARIES} )
