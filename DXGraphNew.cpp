#include "StdAfx.h"
#include "DXGraphNew.h"


// {B98D13E7-55DB-4385-A33D-09FD1BA26338}  
static const GUID CLSID_LavSplitter_Source =   
{ 0xB98D13E7, 0x55DB, 0x4385, { 0xA3, 0x3D, 0x09, 0xFD, 0x1B, 0xA2, 0x63, 0x38 } };  
  
static const GUID CLSID_ffdshowaudec =   
{ 0x0F40E1E5, 0x4F79, 0x4988, { 0xB1, 0xA9, 0xCC, 0x98, 0x79, 0x4E, 0x6B, 0x55 } };  
  
static const GUID CLSID_ffdshowmp4dec =   
{ 0x04fe9017, 0xf873, 0x410e, { 0x87, 0x1e, 0xab, 0x91, 0x66, 0x1a, 0x4e, 0xf7 } };

CDXGraphNew::CDXGraphNew(void)
{
}


CDXGraphNew::~CDXGraphNew(void)
{
	Release();
}


void CDXGraphNew::Release(void)
{
   if (pMediaControl)  
    {  
        pMediaControl->Release();  
        pMediaControl = NULL;  
    }  
    if (pMediaEvent)  
    {  
        pMediaEvent->Release();  
        pMediaEvent = NULL;  
    }  
    if (pBasicVideo)  
    {  
        pBasicVideo->Release();  
        pBasicVideo = NULL;  
    }  
    if (pBasicAudio)  
    {  
        pBasicAudio->Release();  
        pBasicAudio = NULL;  
    }  
    if (pVideoWindow)  
    {  
        pVideoWindow->put_Visible(OAFALSE);  
        pVideoWindow->put_MessageDrain((OAHWND)NULL);  
        pVideoWindow->put_Owner(OAHWND(0));  
        pVideoWindow->Release();  
        pVideoWindow = NULL;  
    }  
    RemoveFromRot(m_dwGraphRegister);  
    if (pGraph)   
    {  
        pGraph->Release();   
        pGraph = NULL;  
    }  
}


bool CDXGraphNew::Create(void)
{
    if (!pGraph)  
    {  
        if (SUCCEEDED(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pGraph)))  
        {  
            AddToRot(pGraph,&m_dwGraphRegister);  
            return QueryInterfaces();         
        }  
    }  
  
    return false; 
}


bool CDXGraphNew::AddFile(CString FileName)
{
//	pGB->AddFilter();
	return false;
}


bool CDXGraphNew::QueryInterfaces(void)
{
    if (pGraph)  
    {  
        HRESULT hr = NOERROR;  
        hr |= pGraph->QueryInterface(IID_IMediaControl, (void **)&pMediaControl);  
        hr |= pGraph->QueryInterface(IID_IMediaEventEx, (void **)&pMediaEvent);  
        hr |= pGraph->QueryInterface(IID_IBasicVideo, (void **)&pBasicVideo);  
        hr |= pGraph->QueryInterface(IID_IBasicAudio, (void **)&pBasicAudio);  
        hr |= pGraph->QueryInterface(IID_IVideoWindow, (void **)&pVideoWindow);  
  
        return SUCCEEDED(hr);  
    }  
	return false;
}


HRESULT CDXGraphNew::AddToRot(IUnknown * pUnkGraph, DWORD * pdwRegister)
{
    IMoniker * pMoniker = NULL;  
    IRunningObjectTable *pROT = NULL;  
  
    if (FAILED(GetRunningObjectTable(0, &pROT)))   
    {  
        return E_FAIL;  
    }  
  
    const size_t STRING_LENGTH = 256;  
  
    WCHAR wsz[STRING_LENGTH];  
  
    StringCchPrintfW(  
        wsz, STRING_LENGTH,   
        L"FilterGraph %08x pid %08x",   
        (DWORD_PTR)pUnkGraph,   
        GetCurrentProcessId()  
        );  
  
    HRESULT hr = CreateItemMoniker(L"!", wsz, &pMoniker);  
    if (SUCCEEDED(hr))   
    {  
        hr = pROT->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE, pUnkGraph,  
            pMoniker, pdwRegister);  
        pMoniker->Release();  
    }  
    pROT->Release();  
  
    return hr;  
}


void CDXGraphNew::RemoveFromRot(DWORD pdwRegister)
{
    IRunningObjectTable *pROT = NULL;  
    if(SUCCEEDED(GetRunningObjectTable(0,&pROT)))  
    {  
        pROT->Revoke(pdwRegister);  
        pROT->Release();  
    }  
}


HRESULT CDXGraphNew::AddFilterByCLSID(IGraphBuilder * pGraph, const GUID& clsid , LPCWCHAR wszName , IBaseFilter ** ppF)
{
    if (!pGraph || !ppF)  
        return E_POINTER;  
    *ppF = 0;  
    IBaseFilter *pF = 0;  
    HRESULT hr = CoCreateInstance(clsid, 0, CLSCTX_INPROC_SERVER, IID_IBaseFilter, reinterpret_cast<void**>(&pF));  
    if (SUCCEEDED(hr))  
    {  
        hr = pGraph->AddFilter(pF, wszName);  
        if (SUCCEEDED(hr))  
            *ppF = pF;  
        else  
            pF->Release();  
    }  
    return hr;  
}


HRESULT CDXGraphNew::GetUnconectedPin(IBaseFilter * pFilter, PIN_DIRECTION PinDir , IPin ** ppPin)
{
    *ppPin = 0;  
    IEnumPins *pEnum = 0;  
    IPin *pPin = 0;  
  
    HRESULT hr = pFilter->EnumPins(&pEnum);  
    if (FAILED(hr))  
    {  
        return hr;  
    }  
    hr = pEnum->Reset();  
    while (pEnum->Next(1,&pPin,NULL) == S_OK)  
    {  
        PIN_DIRECTION ThisPinDirection;  
        pPin->QueryDirection(&ThisPinDirection);  
        if (ThisPinDirection == PinDir)  
        {  
            IPin *pTemp = 0;  
            hr = pPin->ConnectedTo(&pTemp);  
            if (SUCCEEDED(hr))  
            {  
                //当前pin已经连接，无效；  
                pTemp->Release();  
            }   
            else  
            {  
                pEnum->Release();  
                *ppPin = pPin;  
                return S_OK;  
            }             
        }  
        pPin->Release();  
    }  
    pEnum->Release();  
    return E_FAIL;  
}


HRESULT CDXGraphNew::ConnectFilters(IGraphBuilder * pGraph, IPin * pOut, IBaseFilter * pDest)
{
    if ((pGraph == NULL)||(pOut == NULL)||(pDest == NULL))  
        return E_POINTER;  
  
#ifdef _DEBUG  
    PIN_DIRECTION PinDir;  
    pOut->QueryDirection(&PinDir);  
    assert(PinDir == PINDIR_OUTPUT);  
#endif // _DEBUG  
  
    //得到下级filter的输入pin  
    IPin *pIn = 0;  
    HRESULT hr = GetUnconectedPin(pDest,PINDIR_INPUT,&pIn);  
    if (FAILED(hr))  
        return hr;  
  
    hr = pGraph->Connect(pOut,pIn);  
    pIn->Release();  
    return hr;  
}


HRESULT CDXGraphNew::ConnectFilters(IGraphBuilder * pGraph, IBaseFilter * pSrc, IBaseFilter * pDest)
{
    if ((pGraph == NULL)||(pSrc == NULL)||(pDest == NULL))  
        return E_POINTER;  
  
    IPin *pOut = 0;  
    HRESULT hr = GetUnconectedPin(pSrc,PINDIR_OUTPUT,&pOut);  
    if (FAILED(hr))  
        return hr;  
    hr = ConnectFilters(pGraph,pOut,pDest);  
    pOut->Release();  
    return hr;  
}


bool CDXGraphNew::RenderFile(CString fileName)
{
    HRESULT hr = NOERROR;  
/*  
    LPTSTR fileToPlay = fileName.GetBuffer();  
    hr |= AddFilterByCLSID(pGraph,CLSID_LavSplitter_Source,L"Lav Splitter Source",&m_pLavSplitterSource);  
    hr |= m_pLavSplitterSource->QueryInterface(IID_IFileSourceFilter,(void **)&m_pFileSourceFilter);  
    hr |= m_pFileSourceFilter->Load(fileToPlay,NULL);  
    fileName.ReleaseBuffer();  
  
    hr |= AddFilterByCLSID(pGraph,CLSID_LavVideoDecoder,L"Lav Video Decoder",&m_pLavVideoDecoder);  
    hr |= ConnectFilters(pGraph,m_pLavSplitterSource,m_pLavVideoDecoder);  
  
    hr |= AddFilterByCLSID(pGraph,CLSID_LavAudioDecoder,L"Lav Audio Decoder",&m_pLavAudioDecoder);  
    hr |= ConnectFilters(pGraph,m_pLavSplitterSource,m_pLavAudioDecoder);  
  
    hr |= AddFilterByCLSID(pGraph,CLSID_VideoMixingRenderer9,L"Video Mixing Renderer-9",&m_pVideoRenderer);   
    hr |= ConnectFilters(pGraph,m_pLavVideoDecoder,m_pVideoRenderer);  
  
    hr |= AddFilterByCLSID(pGraph,CLSID_AudioRender,L"Audio render",&m_pAudioRender);  
    hr |= ConnectFilters(pGraph,m_pLavAudioDecoder,m_pAudioRender);  
 */ 
    return SUCCEEDED(hr);  
}


bool CDXGraphNew::Run(void)
{
    if (pGraph && pMediaControl)  
    {  
        if (!IsRunning())  
        {  
            if (SUCCEEDED(pMediaControl->Run()))  
            {  
                return true;  
            }  
        }  
        else  
        {  
            return true;  
        }  
    }  
    return false;  
}


bool CDXGraphNew::IsRunning(void)
{
    if (pGraph && pMediaControl)  
    {  
        OAFilterState state = State_Stopped;  
        if (SUCCEEDED(pMediaControl->GetState(10, &state)))  
        {  
            return state == State_Running;  
        }  
    }  
	return false;
}


bool CDXGraphNew::SetDisplayWindow(HWND inWindow)
{
	if (pVideoWindow)
    {
    //  long lVisible;
    //  mVideoWindow->get_Visible(&lVisible);
        // Hide the video window first
        pVideoWindow->put_Visible(OAFALSE);
        pVideoWindow->put_Owner((OAHWND)inWindow);
 
        RECT windowRect;
        ::GetClientRect(inWindow, &windowRect);
        pVideoWindow->put_Left(0);
        pVideoWindow->put_Top(0);
        pVideoWindow->put_Width(windowRect.right - windowRect.left);
        pVideoWindow->put_Height(windowRect.bottom - windowRect.top);
        pVideoWindow->put_WindowStyle(WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
 
        pVideoWindow->put_MessageDrain((OAHWND) inWindow);
        // Restore the video window
        if (inWindow != NULL)
        {
        //  mVideoWindow->put_Visible(lVisible);
            pVideoWindow->put_Visible(OATRUE);
        }
        else
        {
            pVideoWindow->put_Visible(OAFALSE);
        }
        return true;
    }
	return false;
}


bool CDXGraphNew::Stop(void)
{
	if (pGraph && pMediaControl)
    {
        if (!IsStopped())
        {   
            if (SUCCEEDED(pMediaControl->Stop()))
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }
	return false;
}


bool CDXGraphNew::IsStopped(void)
{
	if (pGraph && pMediaControl)
    {
        OAFilterState state = State_Stopped;
        if (SUCCEEDED(pMediaControl->GetState(10, &state)))
        {
            return state == State_Stopped;
        }
    }
	return false;
}


bool CDXGraphNew::IsPaused(void)
{
   if (pGraph && pMediaControl)
    {
        OAFilterState state = State_Stopped;
        if (SUCCEEDED(pMediaControl->GetState(10, &state)))
        {
            return state == State_Paused;
        }
    }
	return false;
}
