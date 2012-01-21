PROJECT(Exercise19)

FIND_PACKAGE(ITK REQUIRED)
IF( ITK_FOUND )
  INCLUDE (${USE_ITK_FILE})
ENDIF( ITK_FOUND )

FIND_PACKAGE(VTK REQUIRED)
IF( VTK_FOUND )
  INCLUDE (${USE_VTK_FILE})
ENDIF( VTK_FOUND )

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

