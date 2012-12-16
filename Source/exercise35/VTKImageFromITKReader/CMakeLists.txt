# To build this exercise, you must build VTK with VTK_USE_GUISUPPORT
# on and VTK_USE_MFC on.
#
# This project is based on "VTK/Examples/GUI/Win32/SampleMFC" -- that
# example was copied and then modified to use vtkImageViewer2 and
# vtkImageReader2Factory to allow opening any image file known by
# vtkImageReader2Factory.
#
PROJECT(VTKImageFromITKReader)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

IF(MSVC80)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
ENDIF(MSVC80)

# VTKMFCSettings.cmake was copied from the CVS HEAD revision of VTK
# on Feb. 9, 2007 (VTK/GUISupport/MFC/VTKMFCSettings.cmake)
#
INCLUDE("VTKMFCSettings.cmake")

IF(VTK_MFC_DELAYLOAD_VTK_DLLS)
  VTK_MFC_ADD_DELAYLOAD_FLAGS(CMAKE_EXE_LINKER_FLAGS
    vtkRendering.dll
    vtkFiltering.dll
    vtkCommon.dll
    )
ENDIF(VTK_MFC_DELAYLOAD_VTK_DLLS)

SET(SRCS
ChildFrm.cpp
MainFrm.cpp
Sample.cpp
Sample.rc
SampleDoc.cpp
SampleView.cpp
StdAfx.cpp
vtkMFCDocument.cpp
vtkMFCRenderView.cpp
vtkMFCView.cpp
vtkKWImage.cxx
vtkKWImageIO.cxx
res/Sample.rc2
)

ADD_EXECUTABLE(VTKImageFromITKReader WIN32 ${SRCS})

IF(VTK_MFC_EXTRA_LIBS)
  TARGET_LINK_LIBRARIES(VTKImageFromITKReader ${VTK_MFC_EXTRA_LIBS})
ENDIF(VTK_MFC_EXTRA_LIBS)

TARGET_LINK_LIBRARIES(VTKImageFromITKReader vtkRendering ITKBasicFilters ITKCommon ITKIO)
