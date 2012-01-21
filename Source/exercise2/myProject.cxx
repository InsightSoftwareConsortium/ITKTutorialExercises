
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkGradientMagnitudeImageFilter.h"

int main( int argc, char ** argv ) 
{
  
  if( argc < 2 )
    {
    std::cerr << "Usage:  myProject   filename2Dimage" << std::endl;
    return 1;
    }
 
  typedef itk::Image< unsigned char, 2 >     ImageType;
  typedef itk::ImageFileReader< ImageType >  ReaderType;
  typedef itk::GradientMagnitudeImageFilter<
                 ImageType, ImageType >      FilterType;

  ReaderType::Pointer  reader  = ReaderType::New();
  FilterType::Pointer  filter  = FilterType::New();

  reader->SetFileName( argv[1] );
  filter->SetInput( reader->GetOutput() );
  filter->Update();

  return 0;

}

