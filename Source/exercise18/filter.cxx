//
//  Excercise on the use of the CannySegmentationLevelSet filter
//

#include "itkSmoothingRecursiveGaussianImageFilter.h"

#include "itkCurvatureAnisotropicDiffusionImageFilter.h"

#include "itkCannySegmentationLevelSetImageFilter.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImage.h"


int main( int argc, char *argv[] )
{


  if( argc < 9 )
    {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImage inputBinaryMask outputImage";
    std::cerr << " advectionScaling curvature Scaling cannyThreshold cannyVariance" << std::endl;
    std::cerr << " maximumIterations" << std::endl;
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


  typedef  itk::CannySegmentationLevelSetImageFilter< 
                                        InternalImageType, 
                                        InternalImageType 
                                                  >  SegmentationFilterType;


  SegmentationFilterType::Pointer  thresholdLevelSet = SegmentationFilterType::New();


  thresholdLevelSet->SetMaximumRMSError( 0.001 );
  thresholdLevelSet->SetNumberOfIterations(atoi(argv[8]));

  smoothing->SetInput( reader2->GetOutput() );

  smoothing->SetNormalizeAcrossScale( true );
  smoothing->SetSigma( 5.0 );  


  thresholdLevelSet->SetInput( smoothing->GetOutput() );
  
  thresholdLevelSet->SetPropagationScaling( 0.0 );
  thresholdLevelSet->SetCurvatureScaling(   atof( argv[ 4 ] ) );
  thresholdLevelSet->SetAdvectionScaling(   atof( argv[ 5 ] ) );

  thresholdLevelSet->SetThreshold(   atof( argv[ 6 ] ) );
  thresholdLevelSet->SetVariance(    atof( argv[ 7 ] ) );

  thresholdLevelSet->SetIsoSurfaceValue( 127.0 );

  thresholdLevelSet->ReverseExpansionDirectionOn();


  // 
  //  Reduce noise on the input image in order to 
  //  simplify canny edges.
  //
  typedef itk::CurvatureAnisotropicDiffusionImageFilter<
                                      InternalImageType,
                                      InternalImageType 
                                          > AnisotropicSmoothingFilterType;


  AnisotropicSmoothingFilterType::Pointer anisotropicSmooting = 
                                    AnisotropicSmoothingFilterType::New();

  anisotropicSmooting->SetInput( reader1->GetOutput() );

  anisotropicSmooting->SetConductanceParameter( 3.0 );
  anisotropicSmooting->SetNumberOfIterations( 5 );
  anisotropicSmooting->SetTimeStep( 0.125 );

  //
  //  Connect inputs to the Shape Detection filter
  //
  thresholdLevelSet->SetInput( smoothing->GetOutput() );

  thresholdLevelSet->SetFeatureImage( anisotropicSmooting->GetOutput() );




  //
  //  Threshold
  //
  typedef itk::BinaryThresholdImageFilter< 
                        InternalImageType, 
                        OutputImageType    >    ThresholdingFilterType;
  
  ThresholdingFilterType::Pointer thresholder = ThresholdingFilterType::New();
                        

  thresholder->SetLowerThreshold( 0.0 ); // cut at the zero set 
  thresholder->SetUpperThreshold( 1e7 ); 

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




