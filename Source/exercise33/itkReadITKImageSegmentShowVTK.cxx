/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkReadITKImageSegmentShowVTK.cxx,v $
  Language:  C++
  Date:      $Date: 2010-04-14 14:12:53 $
  Version:   $Revision: 1.1 $

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "itkCommand.h"
#include "itkImage.h"
#include "itkImageToVTKImageFilter.h"
#include "itkConfidenceConnectedImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkRGBPixel.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "vtkImageImport.h"
#include "vtkImageExport.h"
#include "vtkImageActor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkActor.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkContourFilter.h"
#include "vtkImageData.h"
#include "vtkDataSet.h"
#include "vtkProperty.h"


/**
 * This program implements an example connection between ITK and VTK
 * pipelines.  The combined pipeline flows as follows:
 *
 * itkImageFileReader ==> itkImageToVTKImageFilter ==> vtkImageActor
 *
 * The resulting vtkImageActor is displayed in a vtkRenderWindow.
 */
int main(int argc, char * argv [] )
{
  // Load a color image using ITK and display it with VTK
  if( argc < 2 )
    {
    std::cerr << "Missing parameters" << std::endl;
    std::cerr << "Usage: " << argv[0] << " inputImageFilename " << std::endl;
    return 1;
    }

  try
    {
    typedef unsigned char PixelType;
    const unsigned int Dimension = 2;
    typedef itk::Image< PixelType, Dimension > ImageType;

    typedef itk::ImageFileReader< ImageType > ReaderType;

    ReaderType::Pointer reader  = ReaderType::New();
    reader->SetFileName( argv[1] );
    reader->Update();

    typedef itk::ConfidenceConnectedImageFilter<ImageType,ImageType> SegmentationFilterType;

    SegmentationFilterType::Pointer filter = SegmentationFilterType::New();

    filter->SetInput( reader->GetOutput() );

    filter->SetNumberOfIterations(2);
    filter->SetReplaceValue(255);
    filter->SetMultiplier(2.5);

    ImageType::IndexType index;
    index[0] = 100;
    index[1] = 100;

    filter->SetSeed( index );


	typedef itk::ImageToVTKImageFilter< ImageType > GlueFilterType;
	GlueFilterType::Pointer converter1 = GlueFilterType::New();
	converter1->SetInput(reader->GetOutput());
	converter1->Update();
	GlueFilterType::Pointer converter2 = GlueFilterType::New();
	converter2->SetInput(filter->GetOutput());
	converter2->Update();

    //------------------------------------------------------------------------
    // VTK pipeline.
    //------------------------------------------------------------------------

    // Create a vtkImageActor to help render the image.  Connect it to
    // the converter.
    vtkImageActor* actor = vtkImageActor::New();
	actor->SetInputData(converter1->GetOutput());

    vtkInteractorStyleImage * interactorStyle = vtkInteractorStyleImage::New();


    // Create a renderer, render window, and render window interactor to
    // display the results.
    vtkRenderer* renderer = vtkRenderer::New();
    vtkRenderWindow* renWin = vtkRenderWindow::New();
    vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::New();

    renWin->SetSize(500, 500);
    renWin->AddRenderer(renderer);
    iren->SetRenderWindow(renWin);
    iren->SetInteractorStyle( interactorStyle );

    // Add the vtkImageActor to the renderer for display.
    renderer->AddActor(actor);
    renderer->SetBackground(0.4392, 0.5020, 0.5647);


    // Draw contours around the segmented regions
    vtkContourFilter * contour = vtkContourFilter::New();
	contour->SetInputData(converter2->GetOutput());
	contour->SetValue(0, 128);


    vtkPolyDataMapper * polyMapper = vtkPolyDataMapper::New();
    vtkActor          * polyActor  = vtkActor::New();

    polyActor->SetMapper( polyMapper );
    polyMapper->SetInputConnection( contour->GetOutputPort() );
    polyMapper->ScalarVisibilityOff();


    vtkProperty * property = vtkProperty::New();
    property->SetRepresentationToSurface();
    property->SetColor(1.0,0.0,0.0); //red
    property->SetLineWidth(2.0);

    polyActor->SetProperty( property );

    renderer->AddActor( polyActor );

    // Bring up the render window and begin interaction.
    renWin->Render();
    iren->Start();

    // Release all VTK components
    actor->Delete();
    interactorStyle->Delete();
    polyActor->Delete();
	//converter uses a smart pointer so we do not need to delete it
    contour->Delete();
    property->Delete();
    polyMapper->Delete();
    renWin->Delete();
    renderer->Delete();
    iren->Delete();
    }
  catch( itk::ExceptionObject & e )
    {
    std::cerr << "Exception catched !! " << e << std::endl;
    }

  return 0;
}
