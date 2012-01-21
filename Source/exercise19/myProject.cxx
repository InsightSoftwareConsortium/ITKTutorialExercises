
#include "itkImageFileReader.h"
#include "itkImageToVTKImageFilter.h"
#include "itkImage.h"

#include "vtkImageViewer.h"
#include "vtkRenderWindowInteractor.h"

int main( int argc, char ** argv )
{

  if( argc < 2 )
    {
    std::cerr << "Usage: myProject ImageFileName " << std::endl;
    return 1;
    }

  typedef unsigned short                      PixelType;
  typedef itk::Image< PixelType, 2 >          ImageType;
  typedef itk::ImageFileReader< ImageType >   ReaderType;

  typedef itk::ImageToVTKImageFilter< ImageType >  ConnectorFilterType;

  ReaderType::Pointer  reader = ReaderType::New();
  ConnectorFilterType::Pointer connector = ConnectorFilterType::New();

  reader->SetFileName( argv[1] );
  reader->Update();

  connector->SetInput( reader->GetOutput() );
  
  vtkImageViewer * viewer = vtkImageViewer::New();
  
  vtkRenderWindowInteractor * renderWindowInteractor = vtkRenderWindowInteractor::New();

  viewer->SetSize( 512, 512 );
  viewer->SetupInteractor( renderWindowInteractor );

  viewer->SetInput( connector->GetOutput() );

  viewer->SetColorWindow( 255 );
  viewer->SetColorLevel( 128 );

  viewer->Render(); 
  renderWindowInteractor->Start();
  
  
  return 0;

}



//
//  Exercise:  Add a Gaussian smoothing filter to the 
//             pipeline before passing the image to VTK
//
//
//  HINT:  Instantiate a SmoothingRecursiveGaussianImageFilter,
//         connect its input to the reader and its output to the
//         connector. 
//         
//
//
