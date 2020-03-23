#include "StdAfx.h"
#include "DXGraphVMR9.h"


CDXGraphVMR9::CDXGraphVMR9(void)
{
}


CDXGraphVMR9::~CDXGraphVMR9()
{
}


bool CDXGraphVMR9::Create(HWND hWnd)
{
	if(FAILED(CoCreateInstance(CLSID_FilterGraph,NULL,CLSCTX_INPROC_SERVER,IID_IGraphBuilder,(void **)&g_graph)))
	{
       return false;
	}

	if(FAILED(CoCreateInstance(CLSID_VideoMixingRenderer9,NULL,CLSCTX_INPROC_SERVER,IID_IBaseFilter,(void **)&g_filter)))
	{
        return false;
	}

	//add the VMR-9 to the filter graph
	if(FAILED(g_graph->AddFilter(g_filter, L"VMR9")))
	{
		return false;
	}

	//创建VMRFilterConfig9
	if(FAILED(g_filter->QueryInterface(IID_IVMRFilterConfig9, reinterpret_cast<void**>(&g_filterConfig))))
	{
         return false;
	}

	g_filterConfig->SetRenderingMode(VMR9Mode_Windowless);  //将其配置为WINDOWLESS模式

	//创建VMRWindowlessControl9
	if(FAILED(g_filter->QueryInterface(IID_IVMRWindowlessControl9, reinterpret_cast<void**>(&g_VMR))))
	{
         return false;
	}

	g_VMR->SetVideoClippingWindow(hWnd);    //指定要渲染的窗口为我们的应用程序
                                                                      //主窗口
	//下面的三行描述我们的渲染窗口为整个应用程序客户区（整个配置过程适用于窗口模//式和全屏模式）
	RECT *clientRect = new RECT;
	::GetClientRect(hWnd, clientRect );
	g_VMR->SetVideoPosition( NULL, clientRect );

	g_graph->AddSourceFilter(L"C:\\MyProject\\CircleofLife.mpg", L"source", &g_source);  //将资源载入

	//创建IFilterGrahp2处理媒体流
	if(FAILED(g_graph->QueryInterface(IID_IFilterGraph2,reinterpret_cast<void**>(&g_Graph2))))
	{
		return false;
	}

	
	//指定RENDER渲染设备对上流设备的数据进行处理
	g_Graph2->RenderEx(GetPin(g_source,PINDIR_OUTPUT),AM_RENDEREX_RENDERTOEXISTINGRENDERERS,NULL);

	//创建MediaControl控制播放
	if(FAILED(g_graph->QueryInterface(IID_IMediaControl,reinterpret_cast<void**>(&g_mediaControl))))
	{
		return false;
	}

	return false;
}


IPin* CDXGraphVMR9::GetPin(IBaseFilter * pFilter, PIN_DIRECTION PinDir)
{
    BOOL       bFound = FALSE;
    IEnumPins  *pEnum;
    IPin       *pPin;
    HRESULT hr = pFilter->EnumPins(&pEnum);  //搜索上流设备的PIN
    if (FAILED(hr))
    {
        return NULL;
    }
    while(pEnum->Next(1, &pPin, 0) == S_OK)
    {
        PIN_DIRECTION PinDirThis;
        pPin->QueryDirection(&PinDirThis);
        if (bFound = (PinDir == PinDirThis))   //找到上流设备的输出PIN
            break;
        pPin->Release();
    }
    pEnum->Release();
    
	if(!bFound)MessageBox(NULL,L"Pin连接失败",L"PowerVideo",MB_OK);
    return (bFound ? pPin : NULL); 
}
//该方法主要就是帮助g_Graph2->RenderEx方法和上流设备的媒体输出PIN进行对连
//以便将上流设备解码后的媒体信息流出到RENDER（应用程序创建的渲染器）


void CDXGraphVMR9::play(void)
{
	g_mediaControl->Run();   //播放
}
