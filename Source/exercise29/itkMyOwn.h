/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkMyOwn.h,v $
  Language:  C++
  Date:      $Date: 2010-04-14 14:12:53 $
  Version:   $Revision: 1.1 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itk_MyOwn__h
#define __itk_MyOwn__h

#include "itkObject.h"
#include "itkObjectFactory.h"

namespace itk
{

  class MyOwn : public Object
  {
    public:
      typedef MyOwn                        Self;
      typedef Object                       Superclass;
      typedef SmartPointer< Self >         Pointer;
      typedef SmartPointer< const Self >   ConstPointer;

      itkTypeMacro(MyOwn,Object);
      itkNewMacro(Self)
        
  };

} // end of itk namespace


#endif

