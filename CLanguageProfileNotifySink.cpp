#include "stdafx.h"
#include "LanguageProfileNotifySink.h"

CLanguageProfileNotifySink::CLanguageProfileNotifySink(void)
    : m_ObjRefCount(1)
{}

CLanguageProfileNotifySink::~CLanguageProfileNotifySink(void)
{}

ULONG CLanguageProfileNotifySink::AddRef(void)
{
    return ++m_ObjRefCount;
}

ULONG CLanguageProfileNotifySink::Release(void)
{
    --m_ObjRefCount;
    if (0 != m_ObjRefCount)
        return m_ObjRefCount;
    delete this;
    return 0;
}

HRESULT CLanguageProfileNotifySink::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
    *ppReturn = NULL;

    if (IsEqualIID(riid, IID_IUnknown) ||
        IsEqualIID(riid, IID_ITfLanguageProfileNotifySink)) {
            *ppReturn = (ITfLanguageProfileNotifySink *)this;
    }

    if (*ppReturn) {
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

HRESULT CLanguageProfileNotifySink::OnLanguageChange(LANGID langid, BOOL *pfAccept)
{
    MessageBox(NULL, _T("CLanguageProfileNotifySink::OnLanguageChange"),0,0);
    *pfAccept = TRUE;
    return S_OK;
}

HRESULT CLanguageProfileNotifySink::OnLanguageChanged()
{
    MessageBox(NULL, _T("CLanguageProfileNotifySink::OnLanguageChanged"),0,0);
    return S_OK;
}

HRESULT CLanguageProfileNotifySink::AdviseSink(ITfSource *pSource, DWORD *pdwCookie)
{
    return pSource->AdviseSink(IID_ITfLanguageProfileNotifySink, this, pdwCookie);
}


HRESULT CLanguageProfileNotifySink::UnadviseSink(ITfSource *pSource, DWORD dwCookie)
{
    return pSource->UnadviseSink(dwCookie);
}







CActiveLanguageProfileNotifySink::CActiveLanguageProfileNotifySink(void)
    : m_ObjRefCount(1)
{}

CActiveLanguageProfileNotifySink::~CActiveLanguageProfileNotifySink(void)
{}

ULONG CActiveLanguageProfileNotifySink::AddRef(void)
{
    return ++m_ObjRefCount;
}

ULONG CActiveLanguageProfileNotifySink::Release(void)
{
    --m_ObjRefCount;
    if (0 != m_ObjRefCount)
        return m_ObjRefCount;
    delete this;
    return 0;
}

HRESULT CActiveLanguageProfileNotifySink::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
    *ppReturn = NULL;

    if (IsEqualIID(riid, IID_IUnknown) ||
        IsEqualIID(riid, IID_ITfActiveLanguageProfileNotifySink)) {
            *ppReturn = (ITfActiveLanguageProfileNotifySink*)this;
    }

    if (*ppReturn) {
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

HRESULT CActiveLanguageProfileNotifySink::OnActivated(REFCLSID clsid,REFGUID guidProfile, BOOL fActivated)
{
    if (fActivated)
        MessageBox(NULL, _T("CActiveLanguageProfileNotifySink::OnActivated - Activated!"),0,0);
    return S_OK;
}

HRESULT CActiveLanguageProfileNotifySink::AdviseSink(ITfSource *pSource, DWORD *pdwCookie)
{
    return pSource->AdviseSink(IID_ITfActiveLanguageProfileNotifySink, this, pdwCookie);
}

HRESULT CActiveLanguageProfileNotifySink::UnadviseSink(ITfSource *pSource, DWORD dwCookie)
{
    return pSource->UnadviseSink(dwCookie);
}

