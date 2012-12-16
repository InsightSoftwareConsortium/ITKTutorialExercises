# This project is designed to be built outside the Insight source tree.
PROJECT(Exercise3)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find ITK.
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(Image3_1       Image1.cxx       )
ADD_EXECUTABLE(Image3_1answer Image1answer.cxx )

TARGET_LINK_LIBRARIES(Image3_1       ${ITK_LIBRARIES} )
TARGET_LINK_LIBRARIES(Image3_1answer ${ITK_LIBRARIES} )

