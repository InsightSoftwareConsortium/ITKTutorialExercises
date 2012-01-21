
#include "itkImageFileReader.h"
#include "itkImageToVTKImageFilter.h"
#include "itkSmoothingRecursiveGaussianImageFilter.h"
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

  typedef itk::SmoothingRecursiveGaussianImageFilter< ImageType >  SmoothingFilterType;
  SmoothingFilterType::Pointer smoothing = SmoothingFilterType::New();

  smoothing->SetSigma( 2.0 );
  smoothing->SetNormalizeAcrossScale( true );

  typedef itk::ImageToVTKImageFilter< ImageType >  ConnectorFilterType;

  ReaderType::Pointer  reader = ReaderType::New();
  ConnectorFilterType::Pointer connector = ConnectorFilterType::New();

  reader->SetFileName( argv[1] );
  reader->Update();

  smoothing->SetInput( reader->GetOutput() );
  connector->SetInput( smoothing->GetOutput() );
  
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



