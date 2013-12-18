#pragma once
#include "msctf.h"
#include "LanguageProfileNotifySink.h"

typedef struct
{
    IUnknown *punkID;
    ITextStoreACPSink *pTextStoreACPSink;
    DWORD dwMask;
}ADVISE_SINK, *PADVISE_SINK;    



class CTSFManager
{
public:
    CTSFManager(void);
    ~CTSFManager(void);

    HRESULT Activate();

    HRESULT WatchLanguangeProfileChange();
    HRESULT WatchActiveLanguageProfileChange();

public:
    CComPtr<ITfThreadMgr> m_threadMgr;
    CComPtr<ITfSource> m_source;
    CComPtr<CLanguageProfileNotifySink> m_sink;

    DWORD m_clientId;
    DWORD m_dwCookie;

    
    ULONG m_ObjRefCount;
    ADVISE_SINK m_AdviseSink;

    HWND m_hwnd;
};

