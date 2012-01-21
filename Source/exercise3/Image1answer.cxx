//
//  The following code instantiates an image appropriate for
//  managing digital mamograms.
//
//


#include "itkImage.h"

int main()
{

  typedef itk::Image< unsigned short, 2 > ImageType;

  ImageType::Pointer image = ImageType::New();

  ImageType::SizeType  size;
  size[0] = 1024;
  size[1] = 1024;

  ImageType::IndexType start;
  start[0] = 0;
  start[1] = 0;

  ImageType::RegionType region;
  region.SetSize( size );
  region.SetIndex( start );

  image->SetRegions( region );
  image->Allocate();
  image->FillBuffer( 0 );

  double spacing[3];
  spacing[0] = 0.05;
  spacing[1] = 0.05;

  image->SetSpacing( spacing );

  return 0;
}

