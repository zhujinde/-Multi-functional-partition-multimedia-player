#pragma once

#include "Dshow.h"  

class CDXGraphNew
{
private:
    //DirectShow相关接口成员  
    IGraphBuilder   *pGraph;        //滤波器链表管理器  
    IMediaControl   *pMediaControl; //媒体控制接口，如run、stop、pause  
    IMediaEventEx   *pMediaEvent;   //媒体事件接口  
    IBasicVideo     *pBasicVideo;   //视频基本接口  
    IBasicAudio     *pBasicAudio;   //音频基本接口  
    IVideoWindow    *pVideoWindow;  //视频窗口接口  
  
    DWORD           m_dwGraphRegister;  
	IBaseFilter     *m_pLavSplitterSource;
	IBaseFilter     *m_pFileSourceFilter;
	IBaseFilter     *m_pLavVideoDecoder;
	IBaseFilter     *m_pLavAudioDecoder;
	IBaseFilter     *m_pVideoRenderer;
	IBaseFilter     *m_pAudioRender;

public:
	CDXGraphNew(void);
	~CDXGraphNew(void);
	void Release(void);
	bool Create(void);
	bool AddFile(CString FileName);
	bool QueryInterfaces(void);
	HRESULT AddToRot(IUnknown * pUnkGraph, DWORD * pdwRegister);
	void RemoveFromRot(DWORD pdwRegister);
	HRESULT AddFilterByCLSID(IGraphBuilder * pGraph, const GUID& clsid , LPCWCHAR wszName , IBaseFilter ** ppF);
	HRESULT GetUnconectedPin(IBaseFilter * pFilter, PIN_DIRECTION PinDir , IPin ** ppPin);
	HRESULT ConnectFilters(IGraphBuilder * pGraph, IPin * pOut, IBaseFilter * pDest);
	HRESULT ConnectFilters(IGraphBuilder * pGraph, IBaseFilter * pSrc, IBaseFilter * pDest);
	bool RenderFile(CString fileName);
	bool Run(void);
	bool IsRunning(void);
	bool SetDisplayWindow(HWND inWindow);
	bool Stop(void);
	bool IsStopped(void);
	bool IsPaused(void);
};

