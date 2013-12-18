
// TsfAppForResearchDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "TSFManager.h"


// CTsfAppForResearchDlg dialog
class CTsfAppForResearchDlg : public CDialogEx
{
public:
	CTsfAppForResearchDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_TSFAPPFORRESEARCH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support




	// Implementation
protected:
	HICON m_hIcon;
    CTSFManager *m_pManager;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnEnUpdateEdit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CEdit m_editBox;

	void HookLanguangeProfileChangeEvents();

    afx_msg void OnEnSetfocusEdit();
    afx_msg void OnEnKillfocusEdit();
    afx_msg void OnBnClickedEnableWatcher();
};
