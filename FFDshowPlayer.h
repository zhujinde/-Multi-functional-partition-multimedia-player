#pragma once
#include "Dshow.h"

class CFFDshowPlayer
{
public:
	IGraphBuilder *pGB; //Graph Manager对象
	IVideoWindow *pVW; //设置视频显示窗口对象
	IMediaControl *pMC; //视频播放控制对象
	IBasicAudio *pBA; //音频控制对象
	IBasicVideo *pBV; //视频控制对象
	IMediaEvent *pME; //Dshow事件交互对象

	 IBaseFilter * pF_source;

public:
	CFFDshowPlayer(void);
	~CFFDshowPlayer(void);
	void Release(void);
	bool Create(void);
	bool QueryInterfaces(void);
	bool LoadFile(CString FileName);
};

