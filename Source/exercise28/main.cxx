/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: main.cxx,v $
  Language:  C++
  Date:      $Date: 2010-04-14 14:12:53 $
  Version:   $Revision: 1.1 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImageLinearIteratorWithIndex.h"



int main( int argc, char *argv[] ) 
{
  if( argc < 3 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << "ReflectDiagonalWithIterators   inputFileName outputFileName" << std::endl;
    return -1;
    }




  typedef unsigned char  InputPixelType;
  const   unsigned int   Dimension = 2;

  typedef itk::Image< InputPixelType, Dimension >   ImageType;

  typedef itk::ImageFileReader< ImageType >   ReaderType;

  ReaderType::Pointer reader = ReaderType::New();  

  reader->SetFileName( argv[1] );

  try
    {
    reader->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << "Exception caught " << excp << std::endl;
    return 1;
    }


  ImageType::Pointer inputImage = reader->GetOutput();


  ImageType::Pointer outputImage = ImageType::New();

  typedef ImageType::RegionType    RegionType;
  typedef ImageType::IndexType     IndexType;
  typedef ImageType::SizeType      SizeType;
  typedef ImageType::SpacingType   SpacingType;
  typedef ImageType::PointType     OriginType;


  RegionType  inputRegion   = inputImage->GetLargestPossibleRegion();
  IndexType   inputStart    = inputRegion.GetIndex();
  SizeType    inputSize     = inputRegion.GetSize();
  SpacingType inputSpacing  = inputImage->GetSpacing();

  RegionType  outputRegion;
  IndexType   outputStart;
  SizeType    outputSize;
  SpacingType outputSpacing;

  outputSpacing[0] = inputSpacing[1];
  outputSpacing[1] = inputSpacing[0];

  outputSize[0] = inputSize[1];
  outputSize[1] = inputSize[0];

  outputStart[0] = inputStart[1];
  outputStart[1] = inputStart[0];
  
  outputImage->SetOrigin(  inputImage->GetOrigin() );
  outputImage->SetDirection( inputImage->GetDirection() );

  outputImage->SetSpacing( outputSpacing );

  outputRegion.SetIndex( outputStart );
  outputRegion.SetSize(  outputSize  );

  outputImage->SetRegions( outputRegion );

  outputImage->Allocate();


  typedef itk::ImageLinearConstIteratorWithIndex< ImageType > InputIterator;
  typedef itk::ImageLinearIteratorWithIndex< ImageType >      OutputIterator;


  InputIterator iItr( inputImage, inputRegion );

  OutputIterator oItr( outputImage, outputRegion );


  // Walk the images for inverting the diagonal.
  //
  iItr.SetDirection( 0 );
  oItr.SetDirection( 1 );

  iItr.GoToBegin();
  oItr.GoToBegin();

  while( !iItr.IsAtEnd() )
    {
    while( !iItr.IsAtEndOfLine() )
      {
      oItr.Set( iItr.Get() );
      ++iItr;
      ++oItr;
      }
    iItr.NextLine();
    oItr.NextLine();
    }

  typedef itk::ImageFileWriter< ImageType >   WriterType;

  WriterType::Pointer writer = WriterType::New();

  writer->SetFileName( argv[2] );

  writer->SetInput( outputImage );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << "Exception caught " << excp << std::endl;
    return 1;
    }


  return 0;
}



