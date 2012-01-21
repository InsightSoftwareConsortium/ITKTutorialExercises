# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise14)

# Find ITK.
FIND_PACKAGE(ITK)
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
  MESSAGE(FATAL_ERROR
          "Cannot build without ITK.  Please set ITK_DIR.")
ENDIF(ITK_FOUND)

ADD_EXECUTABLE(filter14       filter.cxx       )

TARGET_LINK_LIBRARIES(filter14       ${ITK_LIBRARIES} )
