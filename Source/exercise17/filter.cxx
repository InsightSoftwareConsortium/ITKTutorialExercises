//
//  Excercise on the use of the ThresholdSegmentationLevelSet filter
//

#include "itkSmoothingRecursiveGaussianImageFilter.h"
#include "itkIntensityWindowingImageFilter.h"

#include "itkThresholdSegmentationLevelSetImageFilter.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImage.h"


int main( int argc, char *argv[] )
{


  if( argc < 10 )
    {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImage inputBinaryMask outputImage";
    std::cerr << " propagationScaling curvatureScaling advectionScaling " << std::endl;
    std::cerr << " lowerThreshold upperThreshold maximumIterations" << std::endl;
    return 1;
    }

  typedef float           InternalPixelType;
  typedef unsigned char   OutputPixelType;
  const   unsigned int    Dimension = 2;
  
  typedef itk::Image< InternalPixelType, Dimension >  InternalImageType;
  typedef itk::Image< OutputPixelType,   Dimension >  OutputImageType;

  typedef  itk::ImageFileReader< InternalImageType > ReaderType;
  typedef  itk::ImageFileWriter<  OutputImageType  > WriterType;


  ReaderType::Pointer reader1 = ReaderType::New();
  ReaderType::Pointer reader2 = ReaderType::New();
  WriterType::Pointer writer  = WriterType::New();

  reader1->SetFileName( argv[1] );
  reader2->SetFileName( argv[2] );
  writer->SetFileName(  argv[3] );


  //
  // Prepare the initial level set image
  //
  typedef   itk::SmoothingRecursiveGaussianImageFilter< 
                               InternalImageType, 
                               InternalImageType >  SmoothingFilterType;

  SmoothingFilterType::Pointer smoothing = SmoothingFilterType::New();



  typedef   itk::IntensityWindowingImageFilter< 
                               InternalImageType, 
                               InternalImageType >  RescaleFilterType;

  RescaleFilterType::Pointer rescaler = RescaleFilterType::New();



  typedef  itk::ThresholdSegmentationLevelSetImageFilter< 
                                        InternalImageType, 
                                        InternalImageType 
                                                  >  SegmentationFilterType;


  SegmentationFilterType::Pointer  thresholdLevelSet = SegmentationFilterType::New();


  thresholdLevelSet->SetMaximumRMSError( 0.001 );
  thresholdLevelSet->SetMaximumIterations( atoi( argv[9] ) );

  smoothing->SetInput( reader2->GetOutput() );

  smoothing->SetNormalizeAcrossScale( true );
  smoothing->SetSigma( 5.0 );  

  // invert the input level set to have negative values inside
  rescaler->SetWindowMinimum(  0  );
  rescaler->SetWindowMaximum( 255 );

  rescaler->SetOutputMinimum(  5.0 );
  rescaler->SetOutputMaximum( -5.0 );  

  rescaler->SetInput( smoothing->GetOutput() );


  thresholdLevelSet->SetInput( rescaler->GetOutput() );
  
  thresholdLevelSet->SetPropagationScaling( atof( argv[ 4 ] ) );
  thresholdLevelSet->SetCurvatureScaling(   atof( argv[ 5 ] ) );
  thresholdLevelSet->SetAdvectionScaling(   atof( argv[ 6 ] ) );

  thresholdLevelSet->SetLowerThreshold(   atof( argv[ 7 ] ) );
  thresholdLevelSet->SetUpperThreshold(   atof( argv[ 8 ] ) );

  thresholdLevelSet->SetIsoSurfaceValue(  0.0 );

  thresholdLevelSet->SetUseNegativeFeaturesOn();


  //
  //  Connect inputs to the Shape Detection filter
  //
  thresholdLevelSet->SetInput( rescaler->GetOutput() );

  thresholdLevelSet->SetFeatureImage( reader1->GetOutput() );




  //
  //  Threshold
  //
  typedef itk::BinaryThresholdImageFilter< 
                        InternalImageType, 
                        OutputImageType    >    ThresholdingFilterType;
  
  ThresholdingFilterType::Pointer thresholder = ThresholdingFilterType::New();
                        

  thresholder->SetLowerThreshold( -1e7  );  
  thresholder->SetUpperThreshold(  0.0  ); // cut at the zero set

  thresholder->SetOutsideValue(  0  );
  thresholder->SetInsideValue(  255 );


  thresholder->SetInput( thresholdLevelSet->GetOutput() );

  writer->SetInput( thresholder->GetOutput() );


  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & excep )
    {
    std::cerr << "Exception caught !" << std::endl;
    std::cerr << excep << std::endl;
    }


  std::cout << "Elapsed Iterations = " << thresholdLevelSet->GetElapsedIterations() << std::endl;
  std::cout << "RMS last change    = " << thresholdLevelSet->GetRMSChange() << std::endl;

  return 0;

}




