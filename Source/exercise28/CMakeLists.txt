PROJECT(Exercise28)

FIND_PACKAGE(ITK REQUIRED)

INCLUDE(${ITK_USE_FILE})

ADD_EXECUTABLE(ReflectDiagonalWithIterators28  main.cxx       )

TARGET_LINK_LIBRARIES(ReflectDiagonalWithIterators28   ${ITK_LIBRARIES} )
