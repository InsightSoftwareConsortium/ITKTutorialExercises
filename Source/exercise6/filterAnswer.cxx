//
//
//    This example illustrates the use of the thresholding filter
//
//

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkThresholdImageFilter.h"


//
//
//     Example program using the  Thresholding filter
//
//

int main( int argc, char * argv[] )
{

  if( argc < 5 ) 
    { 
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "  inputImageFile  outputImageFile  lower upper" << std::endl;
    return 1;
    }


  //
  //  Define the pixel types
  // 

  typedef    unsigned char   PixelType;

  typedef itk::Image< PixelType,  2 >   ImageType;



  //
  //    Instantiate the reader
  //

  typedef itk::ImageFileReader< ImageType >  ReaderType;

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );




  //
  //    Instantiate the filter
  //

  typedef itk::Image< PixelType, 2 >   ImageType;

  typedef itk::ThresholdImageFilter< ImageType >  FilterType;

  FilterType::Pointer filter = FilterType::New();

  filter->SetInput( reader->GetOutput() );


  //  
  //   Take filter parameters from the command line arguments
  //

  
  filter->SetOutsideValue( 0 );

  const PixelType lower = atoi(argv[3] );
  const PixelType upper = atoi(argv[4] );

  filter->ThresholdOutside( lower, upper );



  //
  //   Instantiate the writer
  //

  typedef itk::ImageFileWriter< ImageType >  WriterType;

  WriterType::Pointer writer = WriterType::New();

  writer->SetFileName( argv[2] );
 
  writer->SetInput( filter->GetOutput() );



  //
  //   Execute the writer
  //

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << "Exception caught !" << std::endl;
    std::cerr << excp << std::endl;
    }



  return 0;

}


