/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: main5.cxx,v $
  Language:  C++
  Date:      $Date: 2010-04-14 14:12:53 $
  Version:   $Revision: 1.1 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#include "itkHighlightherImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

//
// This example illustrates how to use a multi-threader filter
//

int main(int argc, char * argv [] )
{

  if( argc < 4 )
    {
    std::cerr << "Missing arguments" << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputFile outputFile numberOfThreads " << std::endl;
    return 1;
    }
 
  typedef itk::Image< unsigned char, 2 >    ImageType;

  typedef itk::ImageFileReader< ImageType >   ReaderType;
  typedef itk::ImageFileWriter< ImageType >   WriterType;

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName( argv[1] );
  writer->SetFileName( argv[2] );
   
  typedef itk::HighlightherImageFilter< ImageType, ImageType >   FilterType;
  FilterType::Pointer filter = FilterType::New();

  filter->SetInput( reader->GetOutput() );
  writer->SetInput( filter->GetOutput() );

  const unsigned int numberOfThread = atoi( argv[3] );

  filter->SetNumberOfThreads( numberOfThread );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << excp << std::endl;
    }

  return 0;

}


