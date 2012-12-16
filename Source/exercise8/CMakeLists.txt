# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise8)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(filter8       filter.cxx       )
ADD_EXECUTABLE(filter8Answer filterAnswer.cxx )

TARGET_LINK_LIBRARIES(filter8       ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES(filter8Answer ${ITK_LIBRARIES} )
