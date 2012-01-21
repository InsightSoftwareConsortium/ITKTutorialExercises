/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkHighlightherImageFilter.h,v $
  Language:  C++
  Date:      $Date: 2010-04-14 14:12:53 $
  Version:   $Revision: 1.1 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkHighlightherImageFilter_h
#define __itkHighlightherImageFilter_h

#include "itkInPlaceImageFilter.h"
#include "itkImageRegionIteratorWithIndex.h"

namespace itk
{
  
/** \class HighlightherImageFilter
 * \brief Implements a filter that high lights the regions managed by each thread
 *
 * \ingroup   IntensityImageFilters     Multithreaded
 */
template <class TInputImage, class TOutputImage>
class ITK_EXPORT HighlightherImageFilter : public InPlaceImageFilter<TInputImage,TOutputImage> 
{
public:
  /** Standard class typedefs. */
  typedef HighlightherImageFilter  Self;
  typedef InPlaceImageFilter<TInputImage,TOutputImage>  Superclass;
  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);
  
  /** Run-time type information (and related methods). */
  itkTypeMacro(HighlightherImageFilter, InPlaceImageFilter);

  /** Some typedefs. */
  typedef TInputImage InputImageType;
  typedef typename    InputImageType::ConstPointer    InputImagePointer;
  typedef typename    InputImageType::RegionType InputImageRegionType; 
  typedef typename    InputImageType::PixelType  InputImagePixelType; 
  typedef TOutputImage OutputImageType;
  typedef typename     OutputImageType::Pointer    OutputImagePointer;
  typedef typename     OutputImageType::RegionType OutputImageRegionType;
  typedef typename     OutputImageType::PixelType  OutputImagePixelType;

  
protected:
  HighlightherImageFilter();
  virtual ~HighlightherImageFilter() {};


  void ThreadedGenerateData(const OutputImageRegionType& outputRegionForThread,
                            int threadId );

private:
  HighlightherImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkHighlightherImageFilter.txx"
#endif

#endif
