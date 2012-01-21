/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: main2.cxx,v $
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
#include "itkImageAdaptor.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRescaleIntensityImageFilter.h"


namespace Accessor 
{

  class Inversor
  {
  public:
    typedef unsigned char   InternalType;
    typedef unsigned char   ExternalType;

    static ExternalType Get( const InternalType & input ) 
      {
        return static_cast<ExternalType>( 255 - input );
      }
  };

}


int main( int argc, char *argv[] ) 
{
  if( argc < 3 )
    {
    std::cerr << "Usage: " << std::endl;
    std::cerr << "ImageAdaptor2   inputFileName outputFileName" << std::endl;
    return -1;
    }


  typedef Accessor::Inversor::InternalType  InputPixelType;
  const   unsigned int   Dimension = 2;

  typedef itk::Image< InputPixelType, Dimension >   ImageType;

  typedef itk::ImageAdaptor<  ImageType, 
                              Accessor::Inversor > ImageAdaptorType;

  ImageAdaptorType::Pointer adaptor = ImageAdaptorType::New();




  typedef itk::ImageFileReader< ImageType >   ReaderType;
  ReaderType::Pointer reader = ReaderType::New();  

  reader->SetFileName( argv[1] );
  reader->Update();

  adaptor->SetImage( reader->GetOutput() );
 



  typedef itk::Image< unsigned char, Dimension >   OutputImageType;
  typedef itk::RescaleIntensityImageFilter< ImageAdaptorType, 
                                            OutputImageType 
                                               >   RescalerType;

  RescalerType::Pointer rescaler = RescalerType::New();
  typedef itk::ImageFileWriter< OutputImageType >   WriterType;
  WriterType::Pointer writer = WriterType::New();


  writer->SetFileName( argv[2] );


  rescaler->SetOutputMinimum(  0  );
  rescaler->SetOutputMaximum( 255 );

  rescaler->SetInput( adaptor );
  writer->SetInput( rescaler->GetOutput() );



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



