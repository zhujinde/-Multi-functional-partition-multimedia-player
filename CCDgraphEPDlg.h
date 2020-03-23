
// CCDgraphEPDlg.h : 头文件
//

#pragma once

#include "DXGraph.h"
#include "afxwin.h"
#include "webofficectrl1.h"

// CCCDgraphEPDlg 对话框
class CCCDgraphEPDlg : public CDialogEx
{
//	CBrush m_brush;   //背景画刷
// 构造
public:
	CCCDgraphEPDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CCDGRAPHEP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CStatusBar m_bar; //状态栏时间

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CString GetFileTitleFromFileName(CString FileName , bool Ext);
//	void CreateGraph(void);
//	void DestroyGraph(void);
	void ShowPicture_1();
	void ShowPicture_2();
	void ShowPicture_3();
	bool IsMp3(CString FilePath);
	void LoadPicture(char szFileName[],CStatic kongjian);
public:
	CDXGraph* pDXGraph;
	CStatic m_PICT;
	CWebofficectrl1 m_office;
	CStatic m_PICT1;
	//重载该函数
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedShowpicture();
	afx_msg void OnStnClickedPict();
	afx_msg void OnBnClickedPlayvideo();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedVideoStop();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);  //设置控件背景透明
	afx_msg void OnBnClickedVolumeSub();
	afx_msg void OnBnClickedVolumeAdd();
	afx_msg void OnBnClickedFullScreen();
};
