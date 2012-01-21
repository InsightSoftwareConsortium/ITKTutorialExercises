
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"


int main( int argc, char * argv[] )
{


  if( argc < 4 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "  inputImageFile  outputImage  sigma " << std::endl;
    return 1;
    }



  const unsigned int Dimension = 2;
  
  typedef unsigned char   InputPixelType;
  typedef unsigned char   OutputPixelType;

  typedef itk::Image< InputPixelType,   Dimension >   InputImageType;
  typedef itk::Image< OutputPixelType,  Dimension >   OutputImageType;

  typedef itk::ImageFileReader< InputImageType   >  ReaderType;
  typedef itk::ImageFileWriter< OutputImageType  >  WriterType;


  typedef itk::GradientMagnitudeRecursiveGaussianImageFilter< 
                                              InputImageType, 
                                              OutputImageType
                                                          >  FilterType;


  //
  // Creation of Reader and Writer filters
  //
  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );


  //
  //  Creation of the filter
  //

  FilterType::Pointer gradient = FilterType::New();

  gradient->SetSigma( atof( argv[3] ) );

  gradient->SetNormalizeAcrossScale( true );


  //
  //  Connecting the data pipeline
  //
  gradient->SetInput(  reader->GetOutput()  );
  writer->SetInput( gradient->GetOutput()   );  



  writer->Update();



  return 0;

}

//
//  Exercise: Run the program with various values of Sigma.
//
//  HINT: Typical values may be: 1.0, 2.0, 3.0, 4.0 
//        keep in mind that sigma is specified in millimeters, not pixels.
//
//

