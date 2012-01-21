//
//  The following code instantiates an image appropriate for
//  managing a CT scan data set.
//
//  Exercise: Create an image type appropriate for managing
//            digital mamograms.
//
//


#include "itkImage.h"

int main()
{

  typedef itk::Image< signed short, 3 > ImageType;

  ImageType::Pointer image = ImageType::New();

  ImageType::SizeType  size;
  size[0] = 512;
  size[1] = 512;
  size[2] =  50;

  ImageType::IndexType start;
  start[0] = 0;
  start[1] = 0;
  start[2] = 0;

  ImageType::RegionType region;
  region.SetSize( size );
  region.SetIndex( start );

  image->SetRegions( region );
  image->Allocate();
  image->FillBuffer( 0 );

  double spacing[3];
  spacing[0] = 0.83;
  spacing[1] = 0.83;
  spacing[2] = 2.15;

  image->SetSpacing( spacing );

  image->Print( std::cout );

  return 0;
}

