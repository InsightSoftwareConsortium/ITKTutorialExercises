/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkMyOwnFactory.cxx,v $
  Language:  C++
  Date:      $Date: 2010-04-14 14:12:53 $
  Version:   $Revision: 1.1 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "itkObjectFactory.h"
#include "itkMyOwn.h"
#include "itkVersion.h"


namespace itk
{


  
/** \class MyOwnFactory
 * \brief Create instances of MyOwn objects using an object factory.
 */
class ITK_EXPORT MyOwnFactory : public ObjectFactoryBase
{
public:  
  /** Standard class typedefs. */
  typedef MyOwnFactory   Self;
  typedef ObjectFactoryBase  Superclass;
  typedef SmartPointer<Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;
  
  /** Class methods used to interface with the registered factories. */
  virtual const char* GetITKSourceVersion(void) const;
  virtual const char* GetDescription(void) const;
    
  /** Method for class instantiation. */
  itkFactorylessNewMacro(Self);
  static MyOwnFactory* FactoryNew() { return new MyOwnFactory;}
  /** Run-time type information (and related methods). */
  itkTypeMacro(MyOwnFactory, ObjectFactoryBase);

  /** Register one factory of this type  */
  static void RegisterOneFactory(void)
  { 
    std::cout << "Calling RegisterOneFactory in MyOwnFactory" << std::endl;
    MyOwnFactory::Pointer myFactory = MyOwnFactory::New();
    ObjectFactoryBase::RegisterFactory( myFactory );
  }
  
protected:
  MyOwnFactory();
  ~MyOwnFactory();

private:
  MyOwnFactory(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};
 
 
extern "C" 
#ifdef _WIN32
__declspec( dllexport ) 
#endif  
  itk::ObjectFactoryBase* itkLoad()
{
  std::cout << "Calling MyOwnFactory itkLoad()" << std::endl;
  return itk::MyOwnFactory::FactoryNew();
}

   

MyOwnFactory::MyOwnFactory()
{
  std::cout << "Constructing MyOwnFactory" << std::endl;

  this->RegisterOverride("itkObject",
                         "itkMyOwn",
                         "This is MyOwn class",
                         1,
                         CreateObjectFunction<MyOwn>::New());
}
  
MyOwnFactory::~MyOwnFactory()
{
  std::cout << "Calling destructor of MyOwnFactory" << std::endl;
}

const char* 
MyOwnFactory::GetITKSourceVersion(void) const
{
  return ITK_SOURCE_VERSION;
}

const char* 
MyOwnFactory::GetDescription(void) const
{
  return "MyOwn Factory, allows the loading of MyOwn objects into insight";
}


} // end namespace itk


