# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise17)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(filter17       filter.cxx       )

TARGET_LINK_LIBRARIES(filter17    ${ITK_LIBRARIES} )
