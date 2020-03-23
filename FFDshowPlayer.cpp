#include "StdAfx.h"
#include "FFDshowPlayer.h"

// {B98D13E7-55DB-4385-A33D-09FD1BA26338}  
static const GUID CLSID_LavSplitter_Source =   
{ 0xB98D13E7, 0x55DB, 0x4385, { 0xA3, 0x3D, 0x09, 0xFD, 0x1B, 0xA2, 0x63, 0x38 } };  
  
static const GUID CLSID_ffdshowaudec =   
{ 0x0F40E1E5, 0x4F79, 0x4988, { 0xB1, 0xA9, 0xCC, 0x98, 0x79, 0x4E, 0x6B, 0x55 } };  
  
static const GUID CLSID_ffdshowmp4dec =   
{ 0x04fe9017, 0xf873, 0x410e, { 0x87, 0x1e, 0xab, 0x91, 0x66, 0x1a, 0x4e, 0xf7 } };

CFFDshowPlayer::CFFDshowPlayer(void)
{
	pGB   = NULL; //Graph Manager对象
	pVW   = NULL; //设置视频显示窗口对象
	pMC   = NULL; //视频播放控制对象
	pBA   = NULL; //音频控制对象
	pBV   = NULL; //视频控制对象
	pME   = NULL;//Dshow事件交互对象

	pF_source = NULL;
}


CFFDshowPlayer::~CFFDshowPlayer(void)
{
	Release();
}


void CFFDshowPlayer::Release(void)
{
	if(pF_source)
	{
		pF_source->Release();
		pF_source = NULL;
	}
    if (pMC)
    {
        pMC->Release();
        pMC = NULL;
    }
    if (pME)
    {
        pME->Release();
        pME = NULL;
    }
    if (pBV)
    {
        pBV->Release();
        pBV = NULL;
    }
    if (pBA)
    {
        pBA->Release();
        pBA = NULL;
    }
    if (pVW)
    {
        pVW->put_Visible(OAFALSE);
        pVW->put_MessageDrain((OAHWND)NULL);
        pVW->put_Owner(OAHWND(0));
        pVW->Release();
        pVW = NULL;
    }

	if (pGB) 
    {
        pGB->Release(); 
        pGB = NULL;
    }
}


bool CFFDshowPlayer::Create(void)
{
    if (!pGB)
    {
        if (SUCCEEDED(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
           IID_IFilterGraph /*IID_IGraphBuilder*/, (void **)&pGB)))
        {

            return QueryInterfaces();
        }
        pGB = 0;
    }
	return false;
}


bool CFFDshowPlayer::QueryInterfaces(void)
{
	if (pGB)
    {
        HRESULT hr = NOERROR;
        hr |= pGB->QueryInterface(IID_IMediaControl, (void **)&pMC);
        hr |= pGB->QueryInterface(IID_IMediaEventEx, (void **)&pME);
        hr |= pGB->QueryInterface(IID_IBasicVideo, (void **)&pBV);
        hr |= pGB->QueryInterface(IID_IBasicAudio, (void **)&pBA);
        hr |= pGB->QueryInterface(IID_IVideoWindow, (void **)&pVW);
	}
	return false;
}


bool CFFDshowPlayer::LoadFile(CString FileName)
{
	HRESULT hr = NOERROR;
  hr = CoCreateInstance(CLSID_AsyncReader, 0, CLSCTX_INPROC_SERVER,IID_IBaseFilter, (void**)(&pF_source));  
    if (FAILED(hr))
	{  
        return false;  
    }  
    hr = pGB->AddFilter(pF_source, L"Lei's Source");  
    if (FAILED(hr)){  
        return false;  
    }  
    IFileSourceFilter* pFileSource;  
    pF_source->QueryInterface(IID_IFileSourceFilter, (void**)&pFileSource);  
    pFileSource->Load(FileName, NULL);  
    pFileSource->Release();  

	return true;
}
