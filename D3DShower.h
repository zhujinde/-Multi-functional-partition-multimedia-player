#pragma once

#include <d3d9.h>

//set '1' to choose a type of file to play
//Read BGRA data
#define LOAD_BGRA    0
//Read YUV420P data
#define LOAD_YUV420P 1


#ifdef __cplusplus
extern "C" {
#endif
#include "libavformat/avformat.h"
#ifdef __cplusplus
} // endof extern "C"
#endif


typedef struct tagHVFrame
{
    int               h;
    unsigned char *   y;
    unsigned char *   u;
    unsigned char *   v;
	int               ypitch;
	int               uvpitch;
} hvframe;

class CD3DShower
{
public:
	RECT m_rtViewport;

	CRITICAL_SECTION  m_critial;

	IDirect3D9 *m_pDirect3D9;
	IDirect3DDevice9 *m_pDirect3DDevice;
	IDirect3DSurface9 *m_pDirect3DSurfaceRender;
public:
	CD3DShower(void);
	~CD3DShower(void);
	void Cleanup(void);
	int InitD3D(HWND hwnd , unsigned long lWidth , unsigned long lHeight);
	bool Render(hvframe/*AVFrame*/ * frame);
};

