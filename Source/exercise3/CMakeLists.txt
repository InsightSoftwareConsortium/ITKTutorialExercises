# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise3)

# Find ITK.
FIND_PACKAGE(ITK)
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
  MESSAGE(FATAL_ERROR
          "Cannot build without ITK.  Please set ITK_DIR.")
ENDIF(ITK_FOUND)

ADD_EXECUTABLE(Image3_1       Image1.cxx       )
ADD_EXECUTABLE(Image3_1answer Image1answer.cxx )

TARGET_LINK_LIBRARIES(Image3_1       ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES(Image3_1answer ${ITK_LIBRARIES} )

