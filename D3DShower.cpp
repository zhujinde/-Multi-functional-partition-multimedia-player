#include "StdAfx.h"
#include "D3DShower.h"


CD3DShower::CD3DShower(void)
{
	m_pDirect3D9= NULL;
	m_pDirect3DDevice= NULL;
	m_pDirect3DSurfaceRender= NULL;
}


CD3DShower::~CD3DShower(void)
{
	Cleanup();
}


void CD3DShower::Cleanup(void)
{
	EnterCriticalSection(&m_critial);
	if(m_pDirect3DSurfaceRender)
		m_pDirect3DSurfaceRender->Release();
	if(m_pDirect3DDevice)
		m_pDirect3DDevice->Release();
	if(m_pDirect3D9)
		m_pDirect3D9->Release();
	LeaveCriticalSection(&m_critial);
}


int CD3DShower::InitD3D(HWND hwnd , unsigned long lWidth , unsigned long lHeight)
{
	HRESULT lRet;
	InitializeCriticalSection(&m_critial);
	Cleanup();

	m_pDirect3D9 = Direct3DCreate9( D3D_SDK_VERSION );
	if( m_pDirect3D9 == NULL )
		return -1;

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	GetClientRect(hwnd,&m_rtViewport);

	lRet=m_pDirect3D9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &m_pDirect3DDevice );

	if(FAILED(lRet))
		return -1;

	lRet=m_pDirect3DDevice->CreateOffscreenPlainSurface(
		lWidth,lHeight,
		(D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2'),
		D3DPOOL_DEFAULT,
		&m_pDirect3DSurfaceRender,
		NULL);

	if(FAILED(lRet))
		return -1;

	return 0;
}


bool CD3DShower::Render(hvframe/*AVFrame */* frame)
{
	HRESULT lRet;
	if(m_pDirect3DSurfaceRender == NULL)
		return false;
	
	D3DLOCKED_RECT d3d_rect;
	lRet=m_pDirect3DSurfaceRender->LockRect(&d3d_rect,NULL,D3DLOCK_DONOTWAIT);
	if(FAILED(lRet))
		return false;

	int uvstep=d3d_rect.Pitch/2;
	char *dest=(char*)d3d_rect.pBits;
	char *vdest=(char*)d3d_rect.pBits+frame->h*d3d_rect.Pitch;
	char *udest=(char*)vdest+frame->h/2*uvstep;
//	char *vdest=(char*)d3d_rect.pBits+frame->height *d3d_rect.Pitch;
//	char *udest=(char*)vdest+frame->height/2*uvstep;


	for(int i=0;i<frame->h;i++)
	{
		memcpy(dest,frame->y,frame->ypitch);
		frame->y+=frame->ypitch;
		dest+=d3d_rect.Pitch;
	}
	for(int i=0;i<frame->h/2;i++)
	{
		memcpy(vdest,frame->v,frame->uvpitch);
		memcpy(udest,frame->u,frame->uvpitch);
		vdest+=uvstep;
		udest+=uvstep;
		frame->v+=frame->uvpitch;
		frame->u+=frame->uvpitch;
	}
/*
	memcpy(dest,frame->y,frame->ypitch*frame->h);

	memcpy(vdest,frame->v,frame->uvpitch*d3d_rect.Pitch/2);
	memcpy(udest,frame->u,frame->uvpitch*d3d_rect.Pitch/2);
*/
/*
	memcpy(dest,frame->data[0],frame->linesize[0] *frame->height);

	memcpy(vdest,frame->data[2],frame->linesize[2] *d3d_rect.Pitch/2);
	memcpy(udest,frame->data[1],frame->linesize[1] *d3d_rect.Pitch/2);
*/
	lRet=m_pDirect3DSurfaceRender->UnlockRect();
	if(FAILED(lRet))
		return false;

	if (m_pDirect3DDevice == NULL)
		return false;

	m_pDirect3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
	m_pDirect3DDevice->BeginScene();
	IDirect3DSurface9 * pBackBuffer = NULL;

	m_pDirect3DDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&pBackBuffer);
	m_pDirect3DDevice->StretchRect(m_pDirect3DSurfaceRender,NULL,pBackBuffer,&m_rtViewport,D3DTEXF_LINEAR);
	m_pDirect3DDevice->EndScene();
	m_pDirect3DDevice->Present( NULL, NULL, NULL, NULL );	

	return false;
}
