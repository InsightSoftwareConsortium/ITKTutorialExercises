# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise10)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(filter10         filter.cxx              )
ADD_EXECUTABLE(filter10Answer1  filterAnswer1.cxx       )
ADD_EXECUTABLE(filter10Answer2  filterAnswer2.cxx       )

TARGET_LINK_LIBRARIES(filter10            ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES(filter10Answer1     ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES(filter10Answer2     ${ITK_LIBRARIES} )
