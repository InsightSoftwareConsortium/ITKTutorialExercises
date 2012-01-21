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


#include "itkFirstQuadrantExtractImageFilter.h"

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main(int argc, char * argv []) 
{
  if( argc < 3 )
    {
    std::cerr << "Missing arguments" << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImage outputImage" << std::endl;
    return 1;
    }
  
  typedef itk::Image< unsigned char, 2 > InputImageType;
  typedef itk::Image< unsigned char, 2 > OutputImageType;

  typedef itk::FirstQuadrantExtractImageFilter< 
                                    InputImageType > FilterType;

  FilterType::Pointer filter = FilterType::New();

  typedef itk::ImageFileReader< InputImageType  >  ReaderType;
  typedef itk::ImageFileWriter< OutputImageType >  WriterType;

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );
  
  filter->SetInput( reader->GetOutput() );
  writer->SetInput( filter->GetOutput() );

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

