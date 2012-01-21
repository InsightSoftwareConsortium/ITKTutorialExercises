/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkFirstQuadrantExtractImageFilter.txx,v $
  Language:  C++
  Date:      $Date: 2010-04-14 14:12:53 $
  Version:   $Revision: 1.1 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkFirstQuadrantExtractImageFilter_txx
#define _itkFirstQuadrantExtractImageFilter_txx

#include "itkFirstQuadrantExtractImageFilter.h"
#include "itkImageRegionIterator.h"

namespace itk
{

template <class TInputImage>
void
FirstQuadrantExtractImageFilter<TInputImage>
::GenerateOutputInformation()
{
  Superclass::GenerateOutputInformation();

  InputImageConstPointer  inputImage  = this->GetInput();
  OutputImagePointer      outputImage = this->GetOutput();

  RegionType inputRegion = inputImage->GetLargestPossibleRegion();
  SizeType   inputSize   = inputRegion.GetSize();
  StartType  inputStart  = inputRegion.GetIndex();

  const unsigned int Dimension = TInputImage::ImageDimension;

  SizeType   outputSize;
  StartType  outputStart;
  
  for( unsigned int i = 0; i < Dimension; i++ )
    {
    outputSize[i]  = inputSize[i] / 2;
    outputStart[i] = inputStart[i];
    }
  
  RegionType outputRegion;

  outputRegion.SetIndex( outputStart );
  outputRegion.SetSize( outputSize );
  
  outputImage->SetLargestPossibleRegion( outputRegion );

  outputImage->SetSpacing(     inputImage->GetSpacing()    );
  outputImage->SetOrigin(      inputImage->GetOrigin()     );
  outputImage->SetDirection(   inputImage->GetDirection()  );

}
  


template <class TInputImage>
void
FirstQuadrantExtractImageFilter<TInputImage>
::GenerateData()
{

  InputImageConstPointer  inputImage  = this->GetInput();
  OutputImagePointer      outputImage = this->GetOutput();

  RegionType  region = outputImage->GetLargestPossibleRegion();

  outputImage->SetRegions( region );
  outputImage->Allocate();

  typedef ImageRegionIterator< TInputImage > ImageRegionIterator;

  typedef ImageRegionConstIterator< TInputImage > ImageRegionConstIterator;

  ImageRegionConstIterator   inputItr(  inputImage,  region );
  ImageRegionIterator        outputItr( outputImage, region );

  inputItr.GoToBegin();
  outputItr.GoToBegin();

  while( ! outputItr.IsAtEnd() )
    {
    outputItr.Set( inputItr.Get() );
    ++inputItr;
    ++outputItr;
    }

}

 

/**
 *
 */
template <class TInputImage>
void 
FirstQuadrantExtractImageFilter<TInputImage>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os,indent);
}

 

  
} // end namespace itk

#endif
