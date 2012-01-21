
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkSmoothingRecursiveGaussianImageFilter.h"


int main( int argc, char * argv[] )
{


  if( argc < 4 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "  inputImageFile  outputImageFile  sigma " << std::endl;
    return 1;
    }



  const unsigned int Dimension = 2;
  
  typedef unsigned char   InputPixelType;
  typedef unsigned char   OutputPixelType;

  typedef itk::Image< InputPixelType,  Dimension >   InputImageType;
  typedef itk::Image< OutputPixelType, Dimension >   OutputImageType;

  typedef itk::ImageFileReader< InputImageType  >  ReaderType;
  typedef itk::ImageFileWriter< OutputImageType >  WriterType;


  typedef itk::SmoothingRecursiveGaussianImageFilter< 
                                              InputImageType, 
                                              InputImageType 
                                                          >  FilterType;


  //
  // Creation of Reader and Writer filters
  //
  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );


  //
  //  Creation of the filte
  //

  FilterType::Pointer smoother = FilterType::New();

  smoother->SetSigma( atof( argv[3] ) );

  smoother->SetNormalizeAcrossScale( true );


  //
  //  Connecting the data pipeline
  //
  smoother->SetInput(  reader->GetOutput()     );
  writer->SetInput(    smoother->GetOutput()   );



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

