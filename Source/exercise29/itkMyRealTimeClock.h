/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkMyRealTimeClock.h,v $
  Language:  C++
  Date:      $Date: 2010-04-14 14:12:53 $
  Version:   $Revision: 1.1 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itk_MyRealTimeClock__h
#define __itk_MyRealTimeClock__h

#include "itkObject.h"
#include "itkObjectFactory.h"
#include "itkRealTimeClock.h"

#include <iostream>

namespace itk
{

  class MyRealTimeClock : public RealTimeClock
  {
    public:
      typedef MyRealTimeClock              Self;
      typedef RealTimeClock                Superclass;
      typedef SmartPointer< Self >         Pointer;
      typedef SmartPointer< const Self >   ConstPointer;

      itkTypeMacro(MyRealTimeClock,RealTimeClock);

      // itkNewMacro(Self);
      
      static Pointer New()
      {
        MyRealTimeClock * rtc = new MyRealTimeClock;
        rtc->Register();  // Reference counting problem.
        return rtc;
      }
     
      
        
    protected:
        MyRealTimeClock()
          {
          std::cout << "Calling Constructor of MyRealTimeClock" << std::endl;
          }
        virtual ~MyRealTimeClock()
          {
          std::cout << "Calling Destructor of MyRealTimeClock" << std::endl;
          }
      virtual void PrintSelf( std::ostream& os, itk::Indent indent ) const
      {
        Superclass::PrintSelf( os, indent );
        std::cout << "Resistance is Futile ! " << std::endl;
        std::cout << "You have been assimilated !! :-) " << std::endl;
      }
    private:
        MyRealTimeClock( const Self & ); // purposely not implemented.
        void operator=( const MyRealTimeClock & ); // purposely not implemented.

  };

} // end of itk namespace


#endif

