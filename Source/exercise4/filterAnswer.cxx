//
//
//    This example illustrates how to read, filter and write an image
//
//

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkGradientAnisotropicDiffusionImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"


int main( int argc, char * argv[] )
{

  if( argc < 5 ) 
    { 
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "  inputImageFile  outputImageFile  numberOfIterations  timeStep" << std::endl;
    return 1;
    }


  typedef    float    InputPixelType;
  typedef    float    OutputPixelType;

  typedef itk::Image< InputPixelType,  2 >   InputImageType;


  //
  //   Instantiate the reader
  //

  typedef itk::ImageFileReader< InputImageType >  ReaderType;

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );




  //
  //    Instantiate the filter
  //

  typedef itk::Image< OutputPixelType, 2 >   OutputImageType;

  typedef itk::GradientAnisotropicDiffusionImageFilter<
                                               InputImageType, 
                                               OutputImageType 
                                                            >  FilterType;

  FilterType::Pointer filter = FilterType::New();

  filter->SetInput( reader->GetOutput() );


  //  
  //   Take filter parameters from the command line arguments
  //

  const unsigned int numberOfIterations = atoi( argv[3] );
  const double       timeStep           = atof( argv[4] );

  filter->SetNumberOfIterations( numberOfIterations );
  filter->SetTimeStep( timeStep );
  filter->SetConductanceParameter( 3.0 );
  



  //
  //    Execute the filter
  //

  try
    {
    filter->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << "Exception caught !" << std::endl;
    std::cerr << excp << std::endl;
    }



  //
  //   Let's now write the output image.
  //   We need to cast from float to unsigned char
  //

  typedef unsigned char WritePixelType;

  typedef itk::Image< WritePixelType, 2 > WriteImageType;

  typedef itk::RescaleIntensityImageFilter< 
               OutputImageType, WriteImageType > RescaleFilterType;

  RescaleFilterType::Pointer rescaler = RescaleFilterType::New();

  rescaler->SetOutputMinimum(   0 );
  rescaler->SetOutputMaximum( 255 );
  
  rescaler->SetInput( filter->GetOutput() );



  //
  //   Instantiate the writer
  //

  typedef itk::ImageFileWriter< WriteImageType >  WriterType;

  WriterType::Pointer writer = WriterType::New();

  writer->SetFileName( argv[2] );
 
  writer->SetInput( rescaler->GetOutput() );


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


