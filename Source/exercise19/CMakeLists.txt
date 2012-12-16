PROJECT(Exercise19)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

FIND_PACKAGE(ITK REQUIRED)
INCLUDE (${USE_ITK_FILE})

FIND_PACKAGE(VTK REQUIRED)
INCLUDE (${USE_VTK_FILE})

INCLUDE_DIRECTORIES( 
  ${Exercise19_SOURCE_DIR} 
  )

ADD_EXECUTABLE( myProject19 MACOSX_BUNDLE myProject.cxx )

TARGET_LINK_LIBRARIES( myProject19
    ${ITK_LIBRARIES}
    vtkRendering vtkGraphics vtkHybrid vtkImaging 
    vtkIO vtkFiltering vtkCommon )

ADD_EXECUTABLE( myProject19Answer MACOSX_BUNDLE myProjectAnswer.cxx )

TARGET_LINK_LIBRARIES( myProject19Answer
    ${ITK_LIBRARIES}
    vtkRendering vtkGraphics vtkHybrid vtkImaging 
    vtkIO vtkFiltering vtkCommon )

