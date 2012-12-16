# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise13)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE( filter13          filter.cxx        )
ADD_EXECUTABLE( filter13Answer    filterAnswer.cxx  )

TARGET_LINK_LIBRARIES( filter13        ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES( filter13Answer  ${ITK_LIBRARIES} )
