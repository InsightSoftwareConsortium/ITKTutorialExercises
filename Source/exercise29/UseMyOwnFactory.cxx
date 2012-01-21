/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: UseMyOwnFactory.cxx,v $
  Language:  C++
  Date:      $Date: 2010-04-14 14:12:53 $
  Version:   $Revision: 1.1 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "itkMyOwn.h"

int main()
{
  typedef  itk::MyOwn   MyOwnType;

  MyOwnType::Pointer myOwnObject = MyOwnType::New();

  return 0;
}


