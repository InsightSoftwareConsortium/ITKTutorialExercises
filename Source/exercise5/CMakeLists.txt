# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise5)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(filter5       filter.cxx       )
ADD_EXECUTABLE(filter5Answer filterAnswer.cxx )

TARGET_LINK_LIBRARIES(filter5       ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES(filter5Answer ${ITK_LIBRARIES} )
