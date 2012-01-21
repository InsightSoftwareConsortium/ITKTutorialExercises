# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise6)

# Find ITK.
FIND_PACKAGE(ITK)
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
  MESSAGE(FATAL_ERROR
          "Cannot build without ITK.  Please set ITK_DIR.")
ENDIF(ITK_FOUND)

ADD_EXECUTABLE(filter6       filter.cxx       )
ADD_EXECUTABLE(filter6Answer filterAnswer.cxx )

TARGET_LINK_LIBRARIES(filter6       ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES(filter6Answer ${ITK_LIBRARIES} )
