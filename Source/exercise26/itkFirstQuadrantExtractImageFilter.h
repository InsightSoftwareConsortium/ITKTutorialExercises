/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkFirstQuadrantExtractImageFilter.h,v $
  Language:  C++
  Date:      $Date: 2010-04-14 14:12:53 $
  Version:   $Revision: 1.1 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkFirstQuadrantExtractImageFilter_h
#define __itkFirstQuadrantExtractImageFilter_h

#include "itkImageToImageFilter.h"

namespace itk
{

/** \class FirstQuadrantExtractImageFilter
 * \brief Extract the N-Dimensional first quadrant from the input image.  This
 * filter does not have any purpose different from showing how a particular
 * filter can define the parameters of its output image.
 *  
 * Therefore, its most interesting method is "GenerateOutputInformation()".
 *
 * \ingroup GeometricTransforms
 */
template <class TInputImage>
class ITK_EXPORT FirstQuadrantExtractImageFilter:
    public ImageToImageFilter<TInputImage,TInputImage>
{
public:
  /** Standard class typedefs. */
  typedef FirstQuadrantExtractImageFilter         Self;
  typedef ImageToImageFilter<TInputImage,TInputImage>  Superclass;
  typedef SmartPointer<Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);  

  /** Run-time type information (and related methods). */
  itkTypeMacro(FirstQuadrantExtractImageFilter, ImageToImageFilter);

  /** typedefs needed for managing the image regions */
  typedef typename TInputImage::RegionType      RegionType;
  typedef typename TInputImage::SizeType        SizeType;
  typedef typename TInputImage::IndexType       StartType;
  typedef typename TInputImage::ConstPointer    InputImageConstPointer;
  typedef typename TInputImage::Pointer         OutputImagePointer;


protected:
  FirstQuadrantExtractImageFilter() {};
  ~FirstQuadrantExtractImageFilter() {};
  void PrintSelf(std::ostream& os, Indent indent) const;

  /** This method defines the metadata of the output image */
  void GenerateOutputInformation();
  
  /** This method performs the operation of copying pixels from the input image
   * into the outpu image. */
  void GenerateData();

private:
  FirstQuadrantExtractImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};

  
} // end namespace itk
  
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkFirstQuadrantExtractImageFilter.txx"
#endif
  
#endif

