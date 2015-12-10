#include "itkImageFileReader.h"
#include "QuickView.h"

int main( int argc, char ** argv )
{
  if( argc < 2 )
    {
    std::cerr << "Usage: myProject ImageFileName " << std::endl;
    return 1;
    }

  typedef unsigned short                      PixelType;
  typedef itk::Image< PixelType, 2 >          ImageType;
  typedef itk::ImageFileReader< ImageType >   ReaderType;

  ReaderType::Pointer  reader = ReaderType::New();

  reader->SetFileName( argv[1] );
  reader->Update();

  QuickView viewer;
  viewer.AddImage(reader->GetOutput());
  viewer.Visualize();

  return 0;
}



//
//  Exercise:  Add a Gaussian smoothing filter to the 
//             pipeline before passing the image to VTK
//
//
//  HINT:  Instantiate a SmoothingRecursiveGaussianImageFilter,
//         connect its input to the reader and its output to the
//         connector. 
//         
//
//
