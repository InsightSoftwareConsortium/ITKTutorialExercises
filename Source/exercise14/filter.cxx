//
//  Excercise on the use of the FastMarching filter
//

#include "itkCurvatureAnisotropicDiffusionImageFilter.h"
#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"
#include "itkSigmoidImageFilter.h"

#include "itkFastMarchingImageFilter.h"
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
    std::cerr << " inputImage  outputImage seedX seedY";
    std::cerr << " BasinMinimum   BorderMinimum   StoppingValue  TimeThreshold   " << std::endl;
    return 1;
    }

  typedef float           InternalPixelType;
  typedef unsigned char   OutputPixelType;
  const   unsigned int    Dimension = 2;
  
  typedef itk::Image< InternalPixelType, Dimension >  InternalImageType;
  typedef itk::Image< OutputPixelType,   Dimension >  OutputImageType;

  typedef  itk::ImageFileReader< InternalImageType > ReaderType;
  typedef  itk::ImageFileWriter<  OutputImageType  > WriterType;

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );


  typedef   itk::CurvatureAnisotropicDiffusionImageFilter< 
                               InternalImageType, 
                               InternalImageType >  SmoothingFilterType;

  SmoothingFilterType::Pointer smoothing = SmoothingFilterType::New();


  typedef   itk::GradientMagnitudeRecursiveGaussianImageFilter< 
                               InternalImageType, 
                               InternalImageType >  GradientFilterType;

  GradientFilterType::Pointer  gradientMagnitude = GradientFilterType::New();

  typedef   itk::SigmoidImageFilter<                               
                               InternalImageType, 
                               InternalImageType >  SigmoidFilterType;


  SigmoidFilterType::Pointer sigmoid = SigmoidFilterType::New();

  sigmoid->SetOutputMinimum(  0.0  );
  sigmoid->SetOutputMaximum(  1.0  );



  typedef  itk::FastMarchingImageFilter< 
                              InternalImageType, 
                              InternalImageType >    FastMarchingFilterType;






  FastMarchingFilterType::Pointer  fastMarching = FastMarchingFilterType::New();




  smoothing->SetInput( reader->GetOutput() );

  gradientMagnitude->SetInput( smoothing->GetOutput() );

  sigmoid->SetInput( gradientMagnitude->GetOutput() );

  fastMarching->SetInput( sigmoid->GetOutput() );
  


  smoothing->SetTimeStep( 0.125 );
  smoothing->SetNumberOfIterations(  5 );
  smoothing->SetConductanceParameter( 3.0 );


  gradientMagnitude->SetSigma(  1.0  );



  const double basinMinimum  = atof( argv[5] );
  const double borderMinimum = atof( argv[6] );

  const double alpha =  - ( borderMinimum - basinMinimum ) / 3.0; 
  const double beta  =    ( borderMinimum + basinMinimum ) / 2.0;

  sigmoid->SetAlpha( alpha );
  sigmoid->SetBeta(  beta  );

  

  typedef FastMarchingFilterType::NodeContainer           NodeContainer;
  typedef FastMarchingFilterType::NodeType                NodeType;

  NodeContainer::Pointer seeds = NodeContainer::New();
  
  InternalImageType::IndexType  seedPosition;
  
  seedPosition[0] = atoi( argv[3] );
  seedPosition[1] = atoi( argv[4] );



  NodeType node;

  const double seedValue = 0.0;
  
  node.SetValue( seedValue );
  node.SetIndex( seedPosition );


  seeds->Initialize();

  seeds->InsertElement( 0, node );

  fastMarching->SetTrialPoints(  seeds  );


  reader->Update();

  fastMarching->SetOutputSize( 
           reader->GetOutput()->GetBufferedRegion().GetSize() );


  fastMarching->SetStoppingValue(  atof( argv[7] ) );


  typedef itk::BinaryThresholdImageFilter< 
                        InternalImageType, 
                        OutputImageType    >    ThresholdingFilterType;
  
  ThresholdingFilterType::Pointer thresholder = ThresholdingFilterType::New();
                        


  const InternalPixelType  timeThreshold = atof( argv[8] );
  
  thresholder->SetLowerThreshold(           0.0  );
  thresholder->SetUpperThreshold( timeThreshold  );

  thresholder->SetOutsideValue(  0  );
  thresholder->SetInsideValue(  255 );


  thresholder->SetInput( fastMarching->GetOutput() );

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


  return 0;

}




