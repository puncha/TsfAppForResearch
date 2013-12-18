
// TsfAppForResearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TsfAppForResearch.h"
#include "TsfAppForResearchDlg.h"
#include "afxdialogex.h"
#include "Msctf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class DWriteEditControlTextEditSink : public ITfTextEditSink
{
private:
    DWORD m_ObjRefCount;
    DWORD m_editCookie;

public:
    //void SetDisplayAttributeMgr(ITfDisplayAttributeMgr* pDisplayAttributeMgr);
    //void SetCategoryMgr(ITfCategoryMgr* pCategoryMgr);

    // IUnknown methods.
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID *ppReturn)
    {
        *ppReturn = NULL;

        if (IsEqualIID(riid, IID_IUnknown) ||
            IsEqualIID(riid, IID_ITfTextEditSink)) {
                *ppReturn = (ITfTextEditSink *)this;
        }

        if (*ppReturn) {
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }
    STDMETHOD_(DWORD, AddRef)(){ return ++m_ObjRefCount; }
    STDMETHOD_(DWORD, Release)() {return S_OK;}

    // ITfTextEditSink
    STDMETHODIMP OnEndEdit(ITfContext *pic, TfEditCookie ecReadOnly, ITfEditRecord *pEditRecord)
    {
        return S_OK;
    }

    HRESULT Advise(ITfContext *pTfContext)
    {
        HRESULT hr = E_FAIL;

        ITfSource *source = nullptr;
        hr = pTfContext->QueryInterface(IID_ITfSource, (void **)&source);
        hr = source->AdviseSink(IID_ITfTextEditSink, (ITfTextEditSink *)this, &m_editCookie);
        return hr;
    }
    HRESULT Unadvise(ITfContext *pTfContext)
    {
        HRESULT hr = E_FAIL;
        if (pTfContext == nullptr) {
            return hr;
        }
        ITfSource *source = nullptr;
        hr = pTfContext->QueryInterface(IID_ITfSource, (void **)&source);
        hr = source->UnadviseSink(m_editCookie);
        return hr;
    }
};



CTsfAppForResearchDlg::CTsfAppForResearchDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CTsfAppForResearchDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTsfAppForResearchDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT, m_editBox);
}

BEGIN_MESSAGE_MAP(CTsfAppForResearchDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //	ON_EN_UPDATE(IDC_EDIT, &CTsfAppForResearchDlg::OnEnUpdateEdit)
    ON_WM_TIMER()
    ON_EN_SETFOCUS(IDC_EDIT, &CTsfAppForResearchDlg::OnEnSetfocusEdit)
    ON_EN_KILLFOCUS(IDC_EDIT, &CTsfAppForResearchDlg::OnEnKillfocusEdit)
    ON_BN_CLICKED(ID_ENABLE_WATCHER, &CTsfAppForResearchDlg::OnBnClickedEnableWatcher)
END_MESSAGE_MAP()

// CTsfAppForResearchDlg message handlers

BOOL CTsfAppForResearchDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    m_pManager = new CTSFManager();
    HRESULT hr = S_OK;
    hr = m_pManager->Activate();
    ASSERT(hr == S_OK);
    this->SetTimer(0, 300, NULL);

    return TRUE;  // return TRUE  unless you set the focus to a control
}



void CTsfAppForResearchDlg::OnTimer(UINT_PTR nIDEvent)
{
    CString szBuffer;

    HRESULT hr = S_OK;
    BOOL bFocused = TRUE;
    hr = m_pManager->m_threadMgr->IsThreadFocus(&bFocused);
    ASSERT(hr == S_OK);
    if (bFocused)
    {
        szBuffer.Append(_T("TSF is on focus. "));
        CComPtr<ITfDocumentMgr> docMgr;
        hr = m_pManager->m_threadMgr->GetFocus(&docMgr);
        if (hr == S_FALSE && docMgr == NULL)
        {
            szBuffer.Append(_T("NO focused document manager."));
        }
        else if (hr == S_OK)
        {
            szBuffer.Append(_T("Focused document manager is accessiable."));
        }

    }
    else
    {
        szBuffer.Append(_T("TSF is NOT on focus."));
    }

    if (szBuffer.IsEmpty())
        szBuffer.Append(_T("Pending..."));
    SetWindowText(szBuffer);

    CDialogEx::OnTimer(nIDEvent);
}


void CTsfAppForResearchDlg::OnBnClickedEnableWatcher()
{
    ASSERT(NULL != m_pManager);
    m_pManager->WatchActiveLanguageProfileChange();
    m_pManager->WatchLanguangeProfileChange();
    this->GetFocus()->EnableWindow(FALSE);
}

void CTsfAppForResearchDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

HCURSOR CTsfAppForResearchDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CTsfAppForResearchDlg::OnEnSetfocusEdit()
{
}

void CTsfAppForResearchDlg::OnEnKillfocusEdit()
{
}

