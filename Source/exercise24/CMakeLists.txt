PROJECT(Exercise24)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

FIND_PACKAGE(ITK REQUIRED)

INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(DividerByTwoImageFilter24  main.cxx       )

TARGET_LINK_LIBRARIES(DividerByTwoImageFilter24   ${ITK_LIBRARIES} )
