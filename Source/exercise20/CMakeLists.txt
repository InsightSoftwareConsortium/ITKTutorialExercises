# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise20)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(registration20       registration.cxx       )
ADD_EXECUTABLE(registration20Answer registrationAnswer.cxx )

TARGET_LINK_LIBRARIES(registration20       ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES(registration20Answer ${ITK_LIBRARIES} )
