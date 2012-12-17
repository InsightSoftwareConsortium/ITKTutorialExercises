# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise12)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE( filter12          filter.cxx        )
ADD_EXECUTABLE( filter12Answer    filterAnswer.cxx  )
ADD_EXECUTABLE( filter12Answer2   filterAnswer2.cxx )
ADD_EXECUTABLE( filter123D        filter3D.cxx      )

TARGET_LINK_LIBRARIES( filter12        ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES( filter12Answer  ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES( filter12Answer2 ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES( filter123D      ${ITK_LIBRARIES} )
