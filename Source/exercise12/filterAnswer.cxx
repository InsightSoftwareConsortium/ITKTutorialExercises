
#include "itkConnectedThresholdImageFilter.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main( int argc, char *argv[] )
{


  if( argc < 7 )
    {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImage  outputImage seedX seedY lower upper" << std::endl;
    return 1;
    }

  typedef unsigned char InputPixelType;
  typedef unsigned char OutputPixelType;
  const   unsigned int  Dimension = 2;

  typedef itk::Image< InputPixelType,  Dimension >  InputImageType;
  typedef itk::Image< OutputPixelType, Dimension >  OutputImageType;

                       
  //
  // We instantiate reader and writer types
  //
  typedef  itk::ImageFileReader< InputImageType   >  ReaderType;
  typedef  itk::ImageFileWriter< OutputImageType  >  WriterType;

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );

  typedef  itk::ConnectedThresholdImageFilter< 
                                    InputImageType, 
                                    OutputImageType > ConnectedFilterType;

  ConnectedFilterType::Pointer connectedThreshold = ConnectedFilterType::New();

  connectedThreshold->SetInput( reader->GetOutput() );

  writer->SetInput( connectedThreshold->GetOutput() );


  connectedThreshold->SetReplaceValue( 255 );

  connectedThreshold->SetLower( atoi( argv[5] ) );
  connectedThreshold->SetUpper( atoi( argv[6] ) );

  InputImageType::IndexType  index;
  index[0] = atoi( argv[3] );
  index[1] = atoi( argv[4] );


  connectedThreshold->SetSeed( index );


  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & excep )
    {
    std::cerr << "Exception caught !" << std::endl;
    std::cerr << excep << std::endl;
    }


  return 0;

}


//
//     Exercise 2:  Replace the ConnectedThresholdImageFilter with 
//                  the IsolatedConnectedImageFilter
//
//     HINT:  Instead of SetUpper() and SetSeed(), this filter requires 
//            the methods SetSeed1(), SetSeed2() and SetUpperValueLimit().
//
//


