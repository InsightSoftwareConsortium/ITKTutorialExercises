
#include "itkImage.h"
#include "itkImageFileReader.h"

#include "itkGradientRecursiveGaussianImageFilter.h"


int main( int argc, char * argv[] )
{


  if( argc < 3 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "  inputImageFile  sigma " << std::endl;
    return 1;
    }



  const unsigned int Dimension = 2;
  
  typedef unsigned char   InputPixelType;

  typedef itk::Image< InputPixelType,  Dimension >   InputImageType;

  typedef itk::ImageFileReader< InputImageType  >  ReaderType;


  typedef itk::GradientRecursiveGaussianImageFilter< 
                                              InputImageType 
                                                          >  FilterType;

  typedef FilterType::OutputImageType   OutputImageType;


  //
  // Creation of Reader filter
  //
  ReaderType::Pointer reader = ReaderType::New();

  reader->SetFileName( argv[1] );


  //
  //  Creation of the filter
  //

  FilterType::Pointer gradient = FilterType::New();

  gradient->SetSigma( atof( argv[2] ) );

  gradient->SetNormalizeAcrossScale( true );


  //
  //  Connecting the data pipeline
  //
  gradient->SetInput(  reader->GetOutput()     );



  gradient->Update();



  return 0;

}

//
//  Exercise: Replace the Gradient filter with the GradientMagnitude
//            filter.
//
//  HINT: Use the filter
//        GradientMagnitudeRecursiveGaussianImageFilter
//
//

