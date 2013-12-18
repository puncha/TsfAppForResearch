#pragma once
#include "msctf.h"

class CLanguageProfileNotifySink : public ITfLanguageProfileNotifySink
{
public:
    CLanguageProfileNotifySink();
    ~CLanguageProfileNotifySink();

    // [IUnknown]
    //
    STDMETHOD_(DWORD, AddRef)();
    STDMETHOD_(DWORD, Release)();
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID *ppReturn);

    // [ITfLanguageProfileNotifySink]
    //
    STDMETHODIMP OnLanguageChange(LANGID langid, BOOL *pfAccept);
    STDMETHODIMP OnLanguageChanged();

    HRESULT AdviseSink(ITfSource *pSource, DWORD *pdwCookie);
    HRESULT UnadviseSink(ITfSource *pSource, DWORD dwCookie);

private:
    DWORD m_ObjRefCount;
};

class CActiveLanguageProfileNotifySink : public ITfActiveLanguageProfileNotifySink
{
public:
    CActiveLanguageProfileNotifySink();
    ~CActiveLanguageProfileNotifySink();

    // [IUnknown]
    //
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID *ppReturn);
    STDMETHOD_(DWORD, AddRef)();
    STDMETHOD_(DWORD, Release)();

    // [CActiveLanguageProfileNotifySink]
    //
    STDMETHODIMP OnActivated(REFCLSID clsid,REFGUID guidProfile, BOOL fActivated);

    HRESULT AdviseSink(ITfSource *pSource, DWORD *pdwCookie);
    HRESULT UnadviseSink(ITfSource *pSource, DWORD dwCookie);

private:
    DWORD m_ObjRefCount;
};

