// SampleDoc.cpp : implementation of the CSampleDoc class
//

#include "stdafx.h"
#include "Sample.h"

#include "SampleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "vtkImageReader2.h"
#include "vtkImageReader2Factory.h"

/////////////////////////////////////////////////////////////////////////////
// CSampleDoc

IMPLEMENT_DYNCREATE(CSampleDoc, vtkMFCDocument)

BEGIN_MESSAGE_MAP(CSampleDoc, vtkMFCDocument)
  //{{AFX_MSG_MAP(CSampleDoc)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleDoc construction/destruction

CSampleDoc::CSampleDoc()
{
  this->Reader = 0;
}

CSampleDoc::~CSampleDoc()
{
  if (this->Reader)
    {
    this->Reader->Delete();
    this->Reader = 0;
    }
}

BOOL CSampleDoc::OnNewDocument()
{
  if (!CDocument::OnNewDocument())
    return FALSE;

  // TODO: add reinitialization code here
  // (SDI documents will reuse this document)

  return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSampleDoc serialization

void CSampleDoc::Serialize(CArchive& ar)
{
  if (ar.IsStoring())
  {
    // TODO: add storing code here
  }
  else
  {
    // TODO: add loading code here
  }
}

/////////////////////////////////////////////////////////////////////////////
// CSampleDoc diagnostics

#ifdef _DEBUG
void CSampleDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void CSampleDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSampleDoc commands

vtkImageReader2* CSampleDoc::GetReader() const
{
  return this->Reader;
}

vtkAlgorithmOutput* CSampleDoc::GetImageViewerInput() const
{
  if (this->Reader)
    {
    return this->Reader->GetOutputPort();
    }

  return 0;
}

BOOL CSampleDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
  if (!vtkMFCDocument::OnOpenDocument(lpszPathName))
    {
    return FALSE;
    }

  if (this->Reader)
    {
    this->Reader->Delete();
    this->Reader = 0;
    }

  this->Reader = vtkImageReader2Factory::CreateImageReader2(lpszPathName);
  if (this->Reader)
    {
    this->Reader->SetFileName(lpszPathName);
    return TRUE;
    }

  // Could not create a reader for the given file...
  //
  return FALSE;
}
