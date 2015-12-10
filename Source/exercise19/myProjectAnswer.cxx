#include "itkImageFileReader.h"
#include "itkSmoothingRecursiveGaussianImageFilter.h"
#include "QuickView.h"

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

  ReaderType::Pointer  reader = ReaderType::New();

  reader->SetFileName( argv[1] );
  reader->Update();

  smoothing->SetInput( reader->GetOutput() );

  QuickView viewer;
  viewer.AddImage(smoothing->GetOutput());
  viewer.Visualize();

  return 0;
}



