# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise11)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(filter11       filter.cxx       )
ADD_EXECUTABLE(filter11Answer filterAnswer.cxx )

TARGET_LINK_LIBRARIES(filter11       ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES(filter11Answer ${ITK_LIBRARIES} )
