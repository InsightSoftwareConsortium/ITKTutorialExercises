//
//
//    This example illustrates the use of the Thresholding filter
//
//

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkBinaryThresholdImageFilter.h"


//
//
//     Example program using the Binary Thresholding filter
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

  typedef    unsigned char   InputPixelType;
  typedef    unsigned char   OutputPixelType;

  typedef itk::Image< InputPixelType,  2 >   InputImageType;



  //
  //    Instantiate the reader
  //

  typedef itk::ImageFileReader< InputImageType >  ReaderType;

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );




  //
  //    Instantiate the filter
  //

  typedef itk::Image< OutputPixelType, 2 >   OutputImageType;

  typedef itk::BinaryThresholdImageFilter<
                                 InputImageType, 
                                 OutputImageType 
                                                  >  FilterType;

  FilterType::Pointer filter = FilterType::New();

  filter->SetInput( reader->GetOutput() );


  //  
  //   Take filter parameters from the command line arguments
  //

  filter->SetLowerThreshold( atoi(argv[3] ) );
  filter->SetUpperThreshold( atoi(argv[4] ) );
  
  filter->SetOutsideValue( 0 );
  filter->SetInsideValue( 255 ); 

  //
  //   Instantiate the writer
  //

  typedef itk::ImageFileWriter< OutputImageType >  WriterType;

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


//
//
//    Exercise: Replace this filter with the itk::ThresholdImageFilter
//
//    HINT: This new filter has three modes of operation. Use the mode
//          ThresholdOutside();
//
//          Note also that this new filter is templated over a single
//          image type.
//


