
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"


#include "itkBinaryDilateImageFilter.h"
#include "itkBinaryBallStructuringElement.h" 

#include "itkBinaryThresholdImageFilter.h"


int main( int argc, char * argv[] )
{


  if( argc < 4 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "  inputImageFile  outputImageFile  threshold " << std::endl;
    return 1;
    }



  const unsigned int Dimension = 2;
  
  typedef unsigned char   InputPixelType;
  typedef unsigned char   OutputPixelType;

  typedef itk::Image< InputPixelType,  Dimension >   InputImageType;
  typedef itk::Image< OutputPixelType, Dimension >   OutputImageType;

  typedef itk::ImageFileReader< InputImageType  >  ReaderType;
  typedef itk::ImageFileWriter< OutputImageType >  WriterType;


  typedef itk::BinaryThresholdImageFilter< 
                                      InputImageType, 
                                      InputImageType 
                                                      >  ThresholdFilterType;


  typedef itk::BinaryBallStructuringElement< 
                      InputPixelType,
                      Dimension  >             StructuringElementType;


  typedef itk::BinaryDilateImageFilter<
                            InputImageType, 
                            OutputImageType, 
                            StructuringElementType >  DilateFilterType;


  //
  // Creation of Reader and Writer filters
  //
  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );


  //
  //  Creation of the thresholding filter used to convert the 
  //  input image into a binary image.
  //
  ThresholdFilterType::Pointer thresholder = ThresholdFilterType::New();

  thresholder->SetOutsideValue(   0 );
  thresholder->SetInsideValue(  255 );

  thresholder->SetLowerThreshold( atoi( argv[3] ) );
  thresholder->SetUpperThreshold( 255 );



  //
  //  Creation of the mathematical morphology components
  //
  StructuringElementType  structuringElement;

  structuringElement.SetRadius( 1 );  // 3x3 structuring element
  structuringElement.CreateStructuringElement();


  DilateFilterType::Pointer dilate = DilateFilterType::New();

  dilate->SetKernel( structuringElement );
  dilate->SetDilateValue( 255 );


  //
  //  Connecting the data pipeline
  //
  thresholder->SetInput(      reader->GetOutput()       );
  dilate->SetInput(           thresholder->GetOutput()  );
  writer->SetInput(           dilate->GetOutput()       );



  writer->Update();



  return 0;

}

//
//  Exercise: Add an Erode filter after the Dilation
//            in order to complete a Closening operation.
//
//  HINT: Instantiate a BinaryErodeImageFilter, connect to it
//        the same structuring element. Connect it in the pipeline
//        between the 'dilate' and 'writer' filters.
//
//

