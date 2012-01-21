/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkMyRealTimeClockFactory.cxx,v $
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
#include "itkMyRealTimeClock.h"
#include "itkVersion.h"


namespace itk
{


  
/** \class MyRealTimeClockFactory
 * \brief Create instances of MyRealTimeClock objects using an object factory.
 */
class ITK_EXPORT MyRealTimeClockFactory : public ObjectFactoryBase
{
public:  
  /** Standard class typedefs. */
  typedef MyRealTimeClockFactory   Self;
  typedef ObjectFactoryBase  Superclass;
  typedef SmartPointer<Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;
  
  /** Class methods used to interface with the registered factories. */
  virtual const char* GetITKSourceVersion(void) const;
  virtual const char* GetDescription(void) const;
    
  /** Method for class instantiation. */
  itkFactorylessNewMacro(Self);
  static MyRealTimeClockFactory* FactoryNew() { return new MyRealTimeClockFactory;}
  /** Run-time type information (and related methods). */
  itkTypeMacro(MyRealTimeClockFactory, ObjectFactoryBase);

  /** Register one factory of this type  */
  static void RegisterOneFactory(void)
  { 
    std::cout << "Calling RegisterOneFactory in MyRealTimeClockFactory" << std::endl;
    MyRealTimeClockFactory::Pointer myFactory = MyRealTimeClockFactory::New();
    ObjectFactoryBase::RegisterFactory( myFactory );
  }
  
protected:
  MyRealTimeClockFactory();
  ~MyRealTimeClockFactory();

private:
  MyRealTimeClockFactory(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};
 
 
extern "C" 
#ifdef _WIN32
__declspec( dllexport ) 
#endif  
  itk::ObjectFactoryBase* itkLoad()
{
  std::cout << "Calling MyRealTimeClockFactory itkLoad()" << std::endl;
  return itk::MyRealTimeClockFactory::FactoryNew();
}

   

MyRealTimeClockFactory::MyRealTimeClockFactory()
{
  std::cout << "Constructing MyRealTimeClockFactory" << std::endl;

  std::string classname1 = typeid(::itk::RealTimeClock).name();
  std::string classname2 = typeid(::itk::MyRealTimeClock).name();

  std::cout << "classname1 = " << classname1 << std::endl;
  std::cout << "classname2 = " << classname2 << std::endl;

  this->RegisterOverride(classname1.c_str(),
                         classname2.c_str(),
                         "Real Time Clock",
                         1,
                         CreateObjectFunction<MyRealTimeClock>::New());
}
  
MyRealTimeClockFactory::~MyRealTimeClockFactory()
{
  std::cout << "Calling destructor of MyRealTimeClockFactory" << std::endl;
}

const char* 
MyRealTimeClockFactory::GetITKSourceVersion(void) const
{
  return ITK_SOURCE_VERSION;
}

const char* 
MyRealTimeClockFactory::GetDescription(void) const
{
  return "MyRealTimeClock Factory, allows the loading of MyRealTimeClock objects into insight";
}


} // end namespace itk


