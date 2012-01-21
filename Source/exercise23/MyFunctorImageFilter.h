/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: MyFunctorImageFilter.h,v $
  Language:  C++
  Date:      $Date: 2010-04-14 14:12:53 $
  Version:   $Revision: 1.1 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __MyFunctorImageFilter_h
#define __MyFunctorImageFilter_h

#include "itkUnaryFunctorImageFilter.h"

namespace itk
{
  
/** \class MyFunctorImageFilter
 * \brief This is a pixel-wise filter that applies a cast operation to every
 * pixel in the input image. 
 *
 * \ingroup IntensityImageFilters  Multithreaded
 */
namespace Functor {  
  
template< class TInput, class TOutput>
class Cast
{
public:
  Cast() {}
  ~Cast() {}
  inline TOutput operator()( const TInput & A )
  {
    return   static_cast<TOutput>( A );
  }
}; 
}
template <class TInputImage, class TOutputImage>
class ITK_EXPORT MyFunctorImageFilter :
    public
UnaryFunctorImageFilter<TInputImage,TOutputImage, 
                        Functor::Cast< typename TInputImage::PixelType, 
                                       typename TOutputImage::PixelType>   >
{
public:
  /** Standard class typedefs. */
  typedef MyFunctorImageFilter  Self;
  typedef UnaryFunctorImageFilter<TInputImage,TOutputImage, 
                                  Functor::Cast< typename TInputImage::PixelType, 
                                                 typename TOutputImage::PixelType> > Superclass;
  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);
  
protected:
  MyFunctorImageFilter() {}
  virtual ~MyFunctorImageFilter() {}

private:
  MyFunctorImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};

} // end namespace itk


#endif
