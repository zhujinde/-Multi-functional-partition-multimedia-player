#pragma once
#include "Dshow.h"
#include "Vmr9.h"

class CDXGraphVMR9
{
private:
	IGraphBuilder*                g_graph;        //FILTER管理器
	IBaseFilter*                  g_filter;         //用于创建VMR9
	IBaseFilter*                  g_source;        //用于流媒体数据处理
	IEnumPins*                    g_enumpins;     //用于获取PIN
	IFilterGraph2*                g_Graph2;             //用于视频流渲染操作
	IMediaControl*                g_mediaControl;   //媒体控制
	IVMRFilterConfig9*            g_filterConfig;     //VMR9配置
	IVMRWindowlessControl9*       g_VMR;         //VMR9的WINDOWED模式控制
	HWND                          hWnd;           //程序主窗口句柄
public:
	CDXGraphVMR9(void);
	~CDXGraphVMR9(void);
	bool Create(HWND hWnd);
	IPin* GetPin(IBaseFilter * pFilter, PIN_DIRECTION PinDir);
	void play(void);
};

