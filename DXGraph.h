#pragma once
#include "Dshow.h"

// Filter graph notification to the specified window
#define WM_GRAPHNOTIFY  (WM_USER+20)
class CDXGraph
{
public:
//	CMediaSource m_source;
private:
    IGraphBuilder *     mGraph;  
    IMediaControl *     mMediaControl;
    IMediaEventEx *     mEvent;
    IBasicVideo *       mBasicVideo;
    IBasicAudio *       mBasicAudio;
    IVideoWindow  *     mVideoWindow;
    IMediaSeeking *     mSeeking;
 
    DWORD               mObjectTableEntry; 
public:
	CDXGraph(void);
	~CDXGraph(void);
	virtual void Release(void);
	void RemoveFromObjectTable(void);
	void AddToObjectTable(void);  //？
	bool SnapshotBitmap(const char * outFile);
	bool RenderFile(const char * inFile);
	long GetAudioBalance(void);     
	bool SetAudioBalance(long inBalance);     // 音量平衡
	long GetAudioVolume(void);
	bool SetAudioVolume(long inVolume);      //调节音量
	bool SetPlaybackRate(double inRate);
	bool GetDuration(double * outDuration);    ////获取播放持续时间
	bool SetStartStopPosition(double inStart, double inStop);
	bool SetCurrentPosition(double inPosition);
	bool GetStopPosition(double * outPosition);
	bool GetCurrentPosition(double * outPosition);
	bool GetFullScreen(void);
	bool SetFullScreen(bool inEnabled);
	bool IsPaused(void);
	bool IsStopped(void);
	bool IsRunning(void);
	bool Pause(void);
	bool Stop(void);
	bool Run(void);
	void HandleEvent(WPARAM inWParam , LPARAM inLParam);
	bool SetNotifyWindow(HWND inWindow);
	bool ResizeVideoWindow(long inLeft, long inTop, long inWidth, long inHeight);
	bool SetDisplayWindow(HWND inWindow);
	void DisconnectFilters(IPin * inOutputPin);   //？
	bool ConnectFilters(IPin * inOutputPin , IPin * inInputPin , const AM_MEDIA_TYPE * inMediaType);
	IMediaEventEx * GetEventHandle(void);
	IGraphBuilder * GetGraph(void);
	bool Attach(IGraphBuilder * inGraphBuilder);
	bool QueryInterfaces(void);
	bool Create(void);
	void LoadFile(void);
	bool EnumPinsOfFilter(IBaseFilter * pFilter, PIN_DIRECTION dir , IEnumPins ** ppEnum, IPin  ** ppPin);
	bool EnumMediaTypesOfPin(IPin * pPin, IEnumMediaTypes ** ppEnum, AM_MEDIA_TYPE  ** ppType);   //？
};

