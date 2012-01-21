# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise9)

# Find ITK.
FIND_PACKAGE(ITK)
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
  MESSAGE(FATAL_ERROR
          "Cannot build without ITK.  Please set ITK_DIR.")
ENDIF(ITK_FOUND)

ADD_EXECUTABLE(filter9       filter.cxx       )

TARGET_LINK_LIBRARIES(filter9       ${ITK_LIBRARIES} )
