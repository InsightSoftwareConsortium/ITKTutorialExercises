//
//
//    This example illustrates the use of Command/Observers
//
//

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkSigmoidImageFilter.h"
#include "itkCommand.h"




//
//   Observer class.
//   Derives from itk::Command and reimplements
//   the Execute() method.
//
class CommandObserver : public itk::Command 
{
public:
  typedef  CommandObserver          Self;
  typedef  itk::Command             Superclass;
  typedef  itk::SmartPointer<Self>  Pointer;
  itkNewMacro( Self );
protected:
  CommandObserver() {};
public:
  typedef   itk::ProcessObject      ProcessType;
  typedef   const ProcessType   *   ProcessPointer;

  void Execute(itk::Object *caller, const itk::EventObject & event)
  {
    Execute( (const itk::Object *)caller, event);
  }

  void Execute(const itk::Object * object, const itk::EventObject & event)
  {
    ProcessPointer filter = dynamic_cast< ProcessPointer >( object );
    if( typeid( event ) == typeid( itk::ProgressEvent ) )
      {
      std::cout << "Progress = " << filter->GetProgress() << std::endl;
      }
    if( typeid( event ) == typeid( itk::StartEvent ) )
      {
      std::cout << "Filter Starting !... " << std::endl;
      std::cout << std::endl;
      }
    if( typeid( event ) == typeid( itk::EndEvent ) )
      {
      std::cout << std::endl;
      std::cout << "Filter Done ! " << std::endl;
      }
  }
};






//
//
//     Example program of Read, Filter and Write pipeline
//
//



int main( int argc, char * argv[] )
{

  if( argc < 5 ) 
    { 
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0] << "  inputImageFile  outputImageFile  sigmoidAlpha  sigmoidBeta " << std::endl;
    return 1;
    }


  //
  //  Pixel types to be used for processing the image
  //  

  typedef    unsigned char   InputPixelType;
  typedef    unsigned char   OutputPixelType;

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

  typedef itk::SigmoidImageFilter<
                                 InputImageType, 
                                 OutputImageType 
                                                  >  FilterType;

  FilterType::Pointer filter = FilterType::New();

  filter->SetInput( reader->GetOutput() );


  //  
  //   Take filter parameters from the command line arguments
  //

  const double  alpha = atof( argv[3] );
  const double  beta  = atof( argv[4] );

  filter->SetAlpha( alpha );
  filter->SetBeta(  beta  );
  


  //
  //   Instantiate the writer
  //

  typedef itk::ImageFileWriter< OutputImageType >  WriterType;

  WriterType::Pointer writer = WriterType::New();

  writer->SetFileName( argv[2] );
 
  writer->SetInput( filter->GetOutput() );





  //
  //   Instantiate and connect an observer
  //

  CommandObserver::Pointer observer = CommandObserver::New();
  
  filter->AddObserver( itk::ProgressEvent() , observer );
  filter->AddObserver( itk::StartEvent() ,    observer );
  filter->AddObserver( itk::EndEvent() ,      observer );



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


