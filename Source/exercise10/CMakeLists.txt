# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise10)

# Find ITK.
FIND_PACKAGE(ITK)
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
  MESSAGE(FATAL_ERROR
          "Cannot build without ITK.  Please set ITK_DIR.")
ENDIF(ITK_FOUND)

ADD_EXECUTABLE(filter10         filter.cxx              )
ADD_EXECUTABLE(filter10Answer1  filterAnswer1.cxx       )
ADD_EXECUTABLE(filter10Answer2  filterAnswer2.cxx       )

TARGET_LINK_LIBRARIES(filter10            ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES(filter10Answer1     ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES(filter10Answer2     ${ITK_LIBRARIES} )
