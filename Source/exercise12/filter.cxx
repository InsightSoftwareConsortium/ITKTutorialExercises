
#include "itkConfidenceConnectedImageFilter.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main( int argc, char *argv[] )
{


  if( argc < 7 )
    {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImage  outputImage seedX seedY multiplier iterations" << std::endl;
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

  typedef  itk::ConfidenceConnectedImageFilter< 
                                    InputImageType, 
                                    OutputImageType > ConnectedFilterType;

  ConnectedFilterType::Pointer confidenceConnected = ConnectedFilterType::New();

  confidenceConnected->SetInput( reader->GetOutput() );

  writer->SetInput( confidenceConnected->GetOutput() );


  confidenceConnected->SetReplaceValue( 255 );

  confidenceConnected->SetMultiplier( atof( argv[5] ) );
  confidenceConnected->SetNumberOfIterations( atoi( argv[6] ) );

  InputImageType::IndexType  index;
  index[0] = atoi( argv[3] );
  index[1] = atoi( argv[4] );


  confidenceConnected->SetSeed( index );

  confidenceConnected->SetInitialNeighborhoodRadius( 2 );


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
//     Exercise:  Replace the ConfidenceConnectedImageFilter with 
//                the ConnectedThresholdImageFilter
//
//     HINT: Instead of SetMultiplier(), SetInitialNeighborhoodRadius() and
//     SetNumberOfIterations(); the new filter has methods SetLower() and
//     SetUpper()
//
//
