/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: main1.cxx,v $
  Language:  C++
  Date:      $Date: 2010-04-14 14:12:53 $
  Version:   $Revision: 1.1 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#include "itkMultiThreader.h"
#include <iostream>



ITK_THREAD_RETURN_TYPE ThreaderCallback( void *arg )
{
   typedef itk::MultiThreader::ThreadInfoStruct  ThreadInfoType;

   ThreadInfoType * infoStruct = static_cast< ThreadInfoType * >( arg );

   unsigned int threadId = infoStruct->ThreadID;

   std::cout << "I'm thread " << threadId << std::endl;

   ITK_THREAD_RETURN_TYPE value;

   return value;
}




int main(int argc, char * argv []) 
{

  if( argc < 2 )
    {
    std::cerr << "Missing arguments" << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " numberOfThreads " << std::endl;
    return 1;
    }
  
 
  itk::MultiThreader::Pointer  threader = itk::MultiThreader::New();

  const unsigned int numberOfThreads = atoi( argv[1] );


  threader->SetNumberOfThreads( numberOfThreads );

  
  threader->SetSingleMethod( ThreaderCallback, NULL );

  threader->SingleMethodExecute();

  return 0;
}

