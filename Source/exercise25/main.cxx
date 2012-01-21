
#include "DividerImageFilter.h"

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main(int argc, char * argv []) 
{
  if( argc < 4 )
    {
    std::cerr << "Missing arguments" << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImage outputImage divisor" << std::endl;
    return 1;
    }
  
  typedef itk::Image< unsigned char,  2 > InputImageType;
  typedef itk::Image< unsigned short, 2 > OutputImageType;

  typedef itk::DividerImageFilter< 
                              InputImageType, 
                              OutputImageType 
                                            > FilterType;

  FilterType::Pointer filter = FilterType::New();

  typedef itk::ImageFileReader< InputImageType  >  ReaderType;
  typedef itk::ImageFileWriter< OutputImageType >  WriterType;

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );
  
  filter->SetInput( reader->GetOutput() );
  writer->SetInput( filter->GetOutput() );

  typedef FilterType::InputRealType    DivisorType;
  
  DivisorType divisor = atof( argv[3] );

  filter->SetDivisor( divisor );

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

