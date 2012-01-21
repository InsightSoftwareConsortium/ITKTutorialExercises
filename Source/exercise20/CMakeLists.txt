# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise20)

# Find ITK.
FIND_PACKAGE(ITK)
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
  MESSAGE(FATAL_ERROR
          "Cannot build without ITK.  Please set ITK_DIR.")
ENDIF(ITK_FOUND)

ADD_EXECUTABLE(registration20       registration.cxx       )
ADD_EXECUTABLE(registration20Answer registrationAnswer.cxx )

TARGET_LINK_LIBRARIES(registration20       ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES(registration20Answer ${ITK_LIBRARIES} )
