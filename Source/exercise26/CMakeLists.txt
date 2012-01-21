PROJECT(Exercise26)

FIND_PACKAGE(ITK REQUIRED)

INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(FirstQuadrantExtractImageFilter26  main.cxx       )

TARGET_LINK_LIBRARIES(FirstQuadrantExtractImageFilter26   ${ITK_LIBRARIES} )
