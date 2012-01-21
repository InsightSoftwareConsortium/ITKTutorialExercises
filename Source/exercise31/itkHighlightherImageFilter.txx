/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkHighlightherImageFilter.txx,v $
  Language:  C++
  Date:      $Date: 2010-04-14 14:12:53 $
  Version:   $Revision: 1.1 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkHighlightherImageFilter_txx
#define _itkHighlightherImageFilter_txx

#include "itkHighlightherImageFilter.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"
#include "itkProgressReporter.h"

namespace itk
{

/**
 * Constructor
 */
template <class TInputImage,class TOutputImage>
HighlightherImageFilter<TInputImage,TOutputImage>
::HighlightherImageFilter()
{
  this->SetNumberOfRequiredInputs( 1 );
  this->InPlaceOff();
}


/**
 * ThreadedGenerateData Performs the pixel-wise addition
 */
template <class TInputImage,class TOutputImage>
void
HighlightherImageFilter<TInputImage,TOutputImage>
::ThreadedGenerateData( const OutputImageRegionType &outputRegionForThread,
                        int threadId)
{
  InputImagePointer  inputPtr = this->GetInput();
  OutputImagePointer outputPtr = this->GetOutput(0);
  
  InputImageRegionType inputRegionForThread;
  this->CallCopyOutputRegionToInputRegion(inputRegionForThread, outputRegionForThread);

  ImageRegionConstIterator<TInputImage>  inputIt(inputPtr, inputRegionForThread);
  ImageRegionIterator<TOutputImage> outputIt(outputPtr, outputRegionForThread);

  ProgressReporter progress(this, threadId, outputRegionForThread.GetNumberOfPixels());

  inputIt.GoToBegin();
  outputIt.GoToBegin();

  const unsigned int hightlight = 10 * threadId;

  while( !inputIt.IsAtEnd() ) 
    {
    outputIt.Set( ( inputIt.Get() / 2 ) + hightlight );
    ++inputIt;
    ++outputIt;
    progress.CompletedPixel();  // potential exception thrown here
    }
}

} // end namespace itk

#endif
