#include "stdafx.h"
#include "TSFManager.h"
#include "LanguageProfileNotifySink.h"

CTSFManager::CTSFManager(void)
    : m_clientId(0)
    , m_dwCookie(0)
    , m_ObjRefCount(1)
    , m_hwnd(NULL)
{
    CoInitializeEx(NULL,  COINIT_APARTMENTTHREADED);
}


CTSFManager::~CTSFManager(void)
{
}

HRESULT CTSFManager::Activate()
{
    HRESULT hr = CoCreateInstance(CLSID_TF_ThreadMgr, NULL, CLSCTX_INPROC_SERVER, IID_ITfThreadMgr,  (LPVOID*)&m_threadMgr);
    hr = m_threadMgr->Activate(&m_clientId);
    return hr;
}

HRESULT CTSFManager::WatchActiveLanguageProfileChange()
{
    HRESULT hr;
    CComPtr<ITfSource> source;
    hr = m_threadMgr->QueryInterface(IID_ITfSource, (LPVOID*)&source);
    ASSERT(hr == S_OK);
    hr = (new CActiveLanguageProfileNotifySink())->AdviseSink(source, &m_dwCookie);
    ASSERT(hr == S_OK);
    return S_OK;
}

HRESULT CTSFManager::WatchLanguangeProfileChange()
{
    HRESULT hr;
    CComPtr<ITfInputProcessorProfiles> profiles;
    hr = CoCreateInstance(CLSID_TF_InputProcessorProfiles, NULL, CLSCTX_INPROC_SERVER, IID_ITfInputProcessorProfiles, (LPVOID*)&profiles);
    ASSERT(hr == S_OK);
    hr = profiles->QueryInterface(IID_ITfSource, (LPVOID*)&m_source);
    ASSERT(hr == S_OK);
    hr = (new CLanguageProfileNotifySink())->AdviseSink(m_source, &m_dwCookie);
    ASSERT(hr == S_OK);
    return hr;
}
