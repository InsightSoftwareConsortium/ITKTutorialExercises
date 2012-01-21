
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCurvatureAnisotropicDiffusionImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"


int main( int argc, char * argv[] )
{


  if( argc < 6 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "  inputImageFile  outputImageFile  timeStep iterations conductance " << std::endl;
    return 1;
    }



  const unsigned int Dimension = 2;
  
  typedef float           InputPixelType;
  typedef float           InternalPixelType;
  typedef unsigned char   WritePixelType;

  typedef itk::Image< InputPixelType,    Dimension >   InputImageType;
  typedef itk::Image< InternalPixelType, Dimension >   InternalImageType;
  typedef itk::Image< WritePixelType,    Dimension >   WriteImageType;

  typedef itk::ImageFileReader< InputImageType  >  ReaderType;
  typedef itk::ImageFileWriter< WriteImageType  >  WriterType;


  typedef itk::CurvatureAnisotropicDiffusionImageFilter< 
                                              InputImageType, 
                                              InternalImageType 
                                                          >  FilterType;

  typedef itk::RescaleIntensityImageFilter< 
                                          InternalImageType,
                                          WriteImageType
                                                        >  RescalerType;

  //
  // Creation of Reader and Writer filters
  //
  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );


  //
  //  Creation of the filte
  //

  FilterType::Pointer smoother = FilterType::New();

  smoother->SetTimeStep(             atof( argv[3] ) );
  smoother->SetNumberOfIterations(   atoi( argv[4] ) );
  smoother->SetConductanceParameter( atof( argv[5] ) );


  // 
  //  Creation of the rescale (and casting) filter
  //  
  
  RescalerType::Pointer rescaler = RescalerType::New();
 
  rescaler->SetOutputMinimum(   0 );
  rescaler->SetOutputMaximum( 255 );


  //
  //  Connecting the data pipeline
  //
  smoother->SetInput(  reader->GetOutput()     );
  rescaler->SetInput(  smoother->GetOutput()   );
  writer->SetInput(    rescaler->GetOutput()   );



  writer->Update();



  return 0;

}


