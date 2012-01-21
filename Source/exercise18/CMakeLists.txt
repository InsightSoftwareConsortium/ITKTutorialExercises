# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise18)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE})
ENDIF(ITK_FOUND)

ADD_EXECUTABLE(filter18       filter.cxx       )

TARGET_LINK_LIBRARIES(filter18   ${ITK_LIBRARIES} )
