# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise12)

# Find ITK.
FIND_PACKAGE(ITK)
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
  MESSAGE(FATAL_ERROR
          "Cannot build without ITK.  Please set ITK_DIR.")
ENDIF(ITK_FOUND)

ADD_EXECUTABLE( filter12          filter.cxx        )
ADD_EXECUTABLE( filter12Answer    filterAnswer.cxx  )
ADD_EXECUTABLE( filter12Answer2   filterAnswer2.cxx )

TARGET_LINK_LIBRARIES( filter12        ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES( filter12Answer  ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES( filter12Answer2 ${ITK_LIBRARIES} )
