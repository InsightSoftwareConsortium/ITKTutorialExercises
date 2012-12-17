
#include "itkIsolatedConnectedImageFilter.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main( int argc, char *argv[] )
{


  if( argc < 8 )
    {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImage  outputImage seed1X seed1Y  seed2X seed2Y  lower" << std::endl;
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

  typedef  itk::IsolatedConnectedImageFilter<
                                    InputImageType,
                                    OutputImageType > ConnectedFilterType;

  ConnectedFilterType::Pointer isolatedConnected = ConnectedFilterType::New();

  isolatedConnected->SetInput( reader->GetOutput() );

  writer->SetInput( isolatedConnected->GetOutput() );


  isolatedConnected->SetReplaceValue( 255 );

  InputImageType::IndexType  seed1;
  seed1[0] = atoi( argv[3] );
  seed1[1] = atoi( argv[4] );

  InputImageType::IndexType  seed2;
  seed2[0] = atoi( argv[5] );
  seed2[1] = atoi( argv[6] );


  isolatedConnected->SetSeed1( seed1 );
  isolatedConnected->SetSeed2( seed2 );

  isolatedConnected->SetLower( atoi( argv[7] ) );

  reader->Update();
  InputImageType::Pointer image = reader->GetOutput();
  isolatedConnected->SetUpperValueLimit( image->GetPixel( seed2 ) );

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


