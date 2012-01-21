//
//
//    This example illustrates the use of the Sigmoid image filter
//
//

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkSigmoidImageFilter.h"


//
//
//     Example program using the Sigmoid filter
//
//

int main( int argc, char * argv[] )
{

  if( argc < 5 ) 
    { 
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "  inputImageFile  outputImageFile  alpha  beta" << std::endl;
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

  typedef itk::SigmoidImageFilter<
                                 InputImageType, 
                                 OutputImageType 
                                                  >  FilterType;

  FilterType::Pointer filter = FilterType::New();

  filter->SetInput( reader->GetOutput() );


  //  
  //   Take filter parameters from the command line arguments
  //

  filter->SetAlpha( atof(argv[3] ) );
  filter->SetBeta(  atof(argv[4] ) );
  
  filter->SetOutputMinimum(  0  );
  filter->SetOutputMaximum( 255 ); 

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
//    Exercise: Test the effect of a negative alpha value.
//
//
//    HINT: run the program with parameters like
// 
//           filter.exe  input.png  output.png  -30 128
//
//


