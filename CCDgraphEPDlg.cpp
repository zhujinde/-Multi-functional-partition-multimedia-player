
// CCDgraphEPDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CCDgraphEP.h"
#include "CCDgraphEPDlg.h"
#include "afxdialogex.h"
#include "D3DShower.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "libavutil/pixdesc.h"
#include "libavutil/imgutils.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#ifdef __cplusplus
} // endof extern "C"
#endif
//#include "SDL/SDL.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCCDgraphEPDlg 对话框

//重载PreTranslateMessage()函数实现退出全屏
BOOL CCCDgraphEPDlg::PreTranslateMessage(MSG* pMsg)
{
  if (pMsg->message == WM_KEYDOWN)  
    {  
         if(pMsg->wParam == VK_ESCAPE)
			 pDXGraph->SetFullScreen(0);
		 return true;
		/*
        switch(pMsg->wParam)  
        {  
            case VK_ESCAPE: //Esc按键事件  
			 {
                pDXGraph->SetFullScreen(0);     
                return true; 
			 }
            case VK_RETURN: //Enter按键事件  
                return true;  
            default:  
                ;  
        }  
		*/
    }  
      
    return CDialogEx::PreTranslateMessage(pMsg);  
}


CCCDgraphEPDlg::CCCDgraphEPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCCDgraphEPDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pDXGraph = new CDXGraph();
}

//控件和对应变量间数据交换
void CCCDgraphEPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICT, m_PICT);
	DDX_Control(pDX, IDC_WEBOFFICECTRL1, m_office);
	DDX_Control(pDX, IDC_PICT1, m_PICT1);
}

//消息映射表
BEGIN_MESSAGE_MAP(CCCDgraphEPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SHOWPICTURE, &CCCDgraphEPDlg::OnBnClickedShowpicture)
	ON_BN_CLICKED(IDC_PLAYVIDEO, &CCCDgraphEPDlg::OnBnClickedPlayvideo)
	ON_STN_CLICKED(IDC_PICT, &CCCDgraphEPDlg::OnStnClickedPict)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_VIDEO_STOP, &CCCDgraphEPDlg::OnBnClickedVideoStop)
	ON_BN_CLICKED(IDCANCEL, &CCCDgraphEPDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CCCDgraphEPDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_VOLUME_SUB, &CCCDgraphEPDlg::OnBnClickedVolumeSub)
	ON_BN_CLICKED(IDC_VOLUME_ADD, &CCCDgraphEPDlg::OnBnClickedVolumeAdd)
	ON_BN_CLICKED(IDC_FULL_SCREEN, &CCCDgraphEPDlg::OnBnClickedFullScreen)
END_MESSAGE_MAP()

// 时钟消息ID
static UINT indicators[] =

{

     IDS_INDICATOR_MESSAGE,

     IDS_INDICATOR_TIME

};


// CCCDgraphEPDlg 消息处理程序

BOOL CCCDgraphEPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//时钟初始化
    SetTimer(1, 1000, NULL);
    m_bar.Create(this); //We create the status bar
    m_bar.SetIndicators(indicators, 2); //Set the number of panes
    CRect rect;
    GetClientRect(&rect);
//Size the two panes
    m_bar.SetPaneInfo(0, IDS_INDICATOR_MESSAGE,
    SBPS_NORMAL, rect.Width() - 220);
    m_bar.SetPaneInfo(1, IDS_INDICATOR_TIME, SBPS_STRETCH, 0);
//This is where we actually draw it on the screen
   RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST,
   IDS_INDICATOR_TIME);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCCDgraphEPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCCDgraphEPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
	//	CDialogEx::OnPaint();

     CPaintDC dc(this); // device context for painting  
     // CPaintDC  dc(this);    
     CRect  rect;    
     GetClientRect(&rect);    
     CDC  dcMem;   //定义一个工具箱（设备上下文）  
     dcMem.CreateCompatibleDC(&dc);///建立关联DC   
     CBitmap  bmpBackground;   //位图对象  
     bmpBackground.LoadBitmap(IDB_BITMAP1);   //IDB_BITMAP是你自己的图对应的ID    
     BITMAP  bitmap;    
     bmpBackground.GetBitmap(&bitmap);  //建立绑定关系  
     CBitmap  *pbmpOld=dcMem.SelectObject(&bmpBackground);   //保存原有CDC对象，并选入新CDC对象入DC  
     dc.SetStretchBltMode(COLORONCOLOR);//防止bmp图片失真  
     dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,  bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);   
     // （个人建议把,rect.Width(),rect.Height()这两个数据 换成你的图片的大小，前提是图片足够大，这样图片不容易失真。关于图片失真，参考：http://       blog.csdn.net/abidepan/article/details/7963929 ）  
     dcMem.SelectObject(pbmpOld);  
     bmpBackground.DeleteObject();  
     dcMem.DeleteDC();  
	}
	
	//初始化时自动加载默认界面
	ShowPicture_1();
    ShowPicture_2();
}


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。

HCURSOR CCCDgraphEPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//读取显示图片
void CCCDgraphEPDlg::OnBnClickedShowpicture()
{
	if(pDXGraph->IsRunning()){
		pDXGraph->Stop();
		pDXGraph->Release();
	}
//文件选择对话框选取文件
	ShowPicture_1();
	CString FilePathName;
    CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
        NULL, 
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        (LPCTSTR)_TEXT("JPG Files (*.jpg)|*.jpg|BMP Files (*.bmp)|*.bmp|PNG Files (*.png)|*.png|All Files (*.*)|*.*||"),
        NULL);
    if(dlg.DoModal()==IDOK)
    {
        FilePathName=dlg.GetPathName(); //文件名保存在了FilePathName里
    }
    else
    {
         return;
    }
// 将Ctring转换为char[]
   CString fileinfo = FilePathName;  
   int len =WideCharToMultiByte(CP_ACP,0,fileinfo,-1,NULL,0,NULL,NULL);    
   char *szFileName =new char[len +1];    
   WideCharToMultiByte(CP_ACP,0,fileinfo,-1,szFileName,len,NULL,NULL );  

   LoadPicture(szFileName,m_PICT1);
}



//视频播放和控制
void CCCDgraphEPDlg::OnBnClickedPlayvideo()
{
	// TODO:
	//pDXGraph = new CDXGraph();
	//文件对话框选择视频文件
	pDXGraph->Release();
	CString FilePathName;
    CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
        NULL, 
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        (LPCTSTR)_TEXT("MPEG file (*.mpg;*.mpeg)|*.mpg;*.mpeg|AVI file (*.avi)|*.avi|wmv file (*.wmv)|*.wmv|Audio file (*.mp3;*.aac)|*.mp3;*.aac|All Files (*.*)|*.*||"),NULL);   //文件格式
    if(dlg.DoModal()==IDOK)
    {
        FilePathName=dlg.GetPathName(); //文件名保存在了FilePathName里
    }
    else
    {
         return;
    }

	if(IsMp3(FilePathName))
		ShowPicture_3();

    CString fileinfo = FilePathName;
    int len =WideCharToMultiByte(CP_ACP,0,fileinfo,-1,NULL,0,NULL,NULL);    
    char *buf =new char[len +1];    
    WideCharToMultiByte(CP_ACP,0,fileinfo,-1,buf,len,NULL,NULL ); 


	if(pDXGraph->Create())
	{
//		char buf[100] = "D:\\Multimedia_files\\kungfu.mpg";
//		char buf[100] = "C:\\MyProject\\Hero.mpg";
		char * pf = buf;
		pDXGraph->RenderFile(pf);
		pDXGraph->SetDisplayWindow(m_PICT.GetSafeHwnd());
		pDXGraph->Pause();
		pDXGraph->Run();
//		ShowPicture_1();
	}
}
void CCCDgraphEPDlg::OnBnClickedVideoStop()
{
	// TODO: 在此添加控件通知处理程序代码
   if(pDXGraph->IsRunning())
		pDXGraph->Pause();
   else if(pDXGraph->IsPaused())
	   pDXGraph->Run();
   else
	   ;
}
void CCCDgraphEPDlg::OnBnClickedVolumeSub()
{
	// TODO: 在此添加控件通知处理程序代码
	long volume = 0;
	volume = pDXGraph->GetAudioVolume();
	pDXGraph->SetAudioVolume(volume-1000);

}
void CCCDgraphEPDlg::OnBnClickedVolumeAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	long volume = 0;
	volume = pDXGraph->GetAudioVolume();
	pDXGraph->SetAudioVolume(volume+1000);
}
void CCCDgraphEPDlg::OnBnClickedFullScreen()
{
	// TODO: 在此添加控件通知处理程序代码
		//	bool GetFullScreen(void);
	//  bool SetFullScreen(bool inEnabled);
	if(pDXGraph->GetFullScreen())
		pDXGraph->SetFullScreen(0);
//	if(pDXGraph->GetFullScreen() == 0)
//		pDXGraph->SetFullScreen(1);
	else
		pDXGraph->SetFullScreen(1);
}


void CCCDgraphEPDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CTime t = CTime::GetCurrentTime();
    m_bar.SetPaneText(1, t.Format(_T("%Y年%m月%d日 星期%w %H:%M:%S")));
    CDialog::OnTimer(nIDEvent);
    CDialogEx::OnTimer(nIDEvent);
}

bool CCCDgraphEPDlg::IsMp3(CString FilePath)
{
    CString  object;
	object=FilePath.Right(4);
	if(object == ".mp3" )
		return true;
	else
		return false;
}



//视频播放器默认背景图片
void CCCDgraphEPDlg::ShowPicture_1()
{
	// TODO:
    char szFileName[128] = "D:\\Multimedia_files\\视频播放器.jpg";
    LoadPicture(szFileName,m_PICT);

}
//图片播放器默认背景图片
void CCCDgraphEPDlg::ShowPicture_2()
{

    char szFileName[128] = "D:\\Multimedia_files\\图片播放器.jpg";
    LoadPicture(szFileName,m_PICT1);

}
//视频播放器播放音频文件时背景图片
void CCCDgraphEPDlg::ShowPicture_3()
{

    char szFileName[128] = "D:\\Multimedia_files\\音乐播放.jpg";
	LoadPicture(szFileName,m_PICT);

}

void CCCDgraphEPDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CCCDgraphEPDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void CCCDgraphEPDlg::OnStnClickedPict()
{
	// TODO: 在此添加控件通知处理程序代码
}

//图片加载函数
void CCCDgraphEPDlg::LoadPicture(char szFileName[],CStatic kongjian)
{
	AVCodecContext *pCodecCtx = NULL;
	AVFrame *pFrame = NULL;
	AVFrame *pFrameYUV = NULL;
	AVCodec *pCodec = NULL;
	AVFormatContext *pFormatCtx = NULL;
	struct SwsContext *img_convert_ctx;
	unsigned char *out_buffer;                                  //ffmpga读取音视频文件，可根据文件类型自动识别
	int ret;

	int decLen = 0;
	int frame = 0;
//    char szFileName[128] = "D:\\Multimedia_files\\音乐播放.jpg";

	av_register_all();
	avformat_network_init();
	pFormatCtx = avformat_alloc_context();

	/* Open input video file */
	if (avformat_open_input(&pFormatCtx,szFileName, NULL, NULL) != 0)
		return ;

	/* Retrieve stream information */
	if (avformat_find_stream_info(pFormatCtx,NULL) < 0)
		return;

	/* Find the first video stream */
	int videoStream = -1;
	for (int i = 0; i < (int)pFormatCtx->nb_streams; i++) 
	{
		if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) 
		{
			videoStream = i;
			break;
		}
	}

	if (videoStream == -1)
		return ;
	// Didn't find a video stream
	/* Get a pointer to the codec context for the video stream */
    
	pCodecCtx = avcodec_alloc_context3(NULL);
    if (!pCodecCtx)
        return ;

    ret = avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[videoStream]->codecpar);
    if (ret < 0)
        return ;

    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL) 
	{
		return ;
	}
	/* Open codec */
	if (avcodec_open2(pCodecCtx, pCodec,NULL)<0)
		return ; // Could not open codec

		//Set up screen
	CRect cr;
	GetClientRect(&cr);
	int w = cr.Width();
	int h = cr.Height();

	pFrame = av_frame_alloc();
	pFrameYUV = av_frame_alloc();

    out_buffer=(unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P,w,h,1));  
    av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize,out_buffer,  
        AV_PIX_FMT_YUV420P,w,h,1);  

	img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
		w, h, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

	/* flag whether we get a decoded yuv frame */
	int packetno = 0;

	AVPacket packet;
	av_init_packet(&packet);
	
	while (av_read_frame(pFormatCtx, &packet) >= 0) 
	{
		/* Is this a packet from the video stream? */
		if (packet.stream_index == videoStream) 
		{
			ret = avcodec_send_packet(pCodecCtx, &packet);
			if (ret != 0)
			{
				break;
			}
			while( avcodec_receive_frame(pCodecCtx, pFrame) != 0);
//			ret = avcodec_receive_frame(pCodecCtx, pFrame);

			img_convert_ctx = sws_getCachedContext(img_convert_ctx,
				pFrame->width, pFrame->height, (AVPixelFormat)(pFrame->format),
				w, h,
				AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
			if (img_convert_ctx == NULL)
			{
				exit(1);
			}
			ret = sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize,
				0, pFrame->height, pFrameYUV->data, pFrameYUV->linesize);

			hvframe frame;
			CD3DShower dd;
//			pFrameYUV->height = h;

			frame.h = h;                                //pFrame->height;
			frame.y = pFrameYUV->data[0];
			frame.u = pFrameYUV->data[1];
			frame.v = pFrameYUV->data[2];
			frame.ypitch = pFrameYUV->linesize[0];
			frame.uvpitch = pFrameYUV->linesize[1];

			dd.InitD3D(kongjian.GetSafeHwnd(),w,h);        //m_PICT为控件
			dd.Render(&frame/* pFrameYUV*/);
		}
	}

	/* Free the YUV frame */
	av_free(pFrame);

	av_free(out_buffer);

	av_free(pFrameYUV);

	/* Close the codec */
	avcodec_close(pCodecCtx);

	/* Close the video file */
	avformat_close_input(&pFormatCtx);
}



/*   //设置控件背景透明
HBRUSH CCCDgraphEPDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)   
{  
 HBRUSH hbr = CCCDgraphEPDlg::OnCtlColor(pDC, pWnd, nCtlColor);  
  
 if( nCtlColor == CTLCOLOR_STATIC)        
 {      
  pDC->SetBkMode(TRANSPARENT);   //设置背景透明   
  return   HBRUSH(GetStockObject(HOLLOW_BRUSH));  
 }   
 return hbr;  
}
*/