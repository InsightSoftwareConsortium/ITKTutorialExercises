// ITK-MFCDlg.h : header file
//

#pragma once

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCurvatureFlowImageFilter.h"


// CITKMFCDlg dialog
class CITKMFCDlg : public CDialog
{
// Construction
public:
  CITKMFCDlg(CWnd* pParent = NULL);  // standard constructor

// Dialog Data
  enum { IDD = IDD_ITKMFC_DIALOG };

  protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support


// Implementation
protected:
  HICON m_hIcon;

  // Generated message map functions
  virtual BOOL OnInitDialog();
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void OnPaint();

  afx_msg void LoadInputImage();
  afx_msg void RunImageFilter();
  afx_msg void SaveOutputImage();

  afx_msg void CancelFiltering();

  afx_msg void OnHScroll(
    UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

  afx_msg HCURSOR OnQueryDragIcon();
  DECLARE_MESSAGE_MAP()

private:

  typedef float                               PixelType;  
  typedef itk::Image< PixelType, 2 >          ImageType;
  typedef itk::ImageFileReader< ImageType >   ReaderType;
  typedef itk::ImageFileWriter< ImageType >   WriterType;
  typedef itk::CurvatureFlowImageFilter< 
                     ImageType, ImageType >   FilterType;

  ReaderType::Pointer     m_Reader;
  WriterType::Pointer     m_Writer;
  FilterType::Pointer     m_Filter;

  CSliderCtrl             m_NumberOfIterationsSlider;

  CProgressCtrl           m_ProgressBar;

  bool                    m_CancelFilter;

  typedef itk::ReceptorMemberCommand< CITKMFCDlg > ReceptorCommandType;

  ReceptorCommandType::Pointer m_ReceptorCommand;

  void UpdateProgressBar( const itk::EventObject & event );


};
