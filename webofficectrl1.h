#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CWebofficectrl1 包装类

class CWebofficectrl1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CWebofficectrl1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xE77E049B, 0x23FC, 0x4DB8, { 0xB7, 0x56, 0x60, 0x52, 0x9A, 0x35, 0xFA, 0xD5 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:
enum
{
    custColorToolBarBKColor = 0,
    custColorToolBarMiddleColor = 1,
    custColorToolBarTopColor = 2,
    custColorToolBarBottomColor = 3,
    custColorScrollArrow = 4,
    custColorScrollBK = 5,
    custColorScrollDimBK = 6,
    custColorScrollThumb = 7,
    custColorScrollPushed = 8,
    custColorCount = 9
}enumCustColorType;


// 操作
public:

// _DWebOffice

// Functions
//

	LPDISPATCH GetDocumentObject()
	{
		LPDISPATCH result;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long FtpConnect(LPCTSTR strURL, long lPort, LPCTSTR strUser, LPCTSTR strPwd)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strURL, lPort, strUser, strPwd);
		return result;
	}
	long FtpDisConnect()
	{
		long result;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long FtpGetFile(LPCTSTR strRemoteFile, LPCTSTR strLocalFile)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strRemoteFile, strLocalFile);
		return result;
	}
	long FtpPutFile(LPCTSTR strLocalFile, LPCTSTR strRemoteFile, long blOverWrite)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strLocalFile, strRemoteFile, blOverWrite);
		return result;
	}
	long HideMenuItem(long lMenuType)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lMenuType);
		return result;
	}
	long HttpInit()
	{
		long result;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString HttpPost(LPCTSTR strHttpURL)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strHttpURL);
		return result;
	}
	long HttpAddPostBuffer(LPCTSTR strName, LPCTSTR strRelateFile, LPCTSTR pbBuffer, long lLen)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strName, strRelateFile, pbBuffer, lLen);
		return result;
	}
	long HttpAddPostFile(LPCTSTR strName, LPCTSTR strFile)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strName, strFile);
		return result;
	}
	long HttpAddPostString(LPCTSTR strName, LPCTSTR strValue)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strName, strValue);
		return result;
	}
	long HttpAddPostValue(LPCTSTR strName, long lValue)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strName, lValue);
		return result;
	}
	long IsOpened()
	{
		long result;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IsSaved()
	{
		long result;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long LoadOriginalFile(LPCTSTR pcFileNameOrUrl, LPCTSTR pcType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pcFileNameOrUrl, pcType);
		return result;
	}
	long SaveTo(LPCTSTR pcFileNameOrUrl)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pcFileNameOrUrl);
		return result;
	}
	long PrintDoc(long blShowDlg)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, blShowDlg);
		return result;
	}
	long HttpAddPostCurrFile2(LPCTSTR strName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strName);
		return result;
	}
	long ProtectDoc(long lProOrUn, long lType, LPCTSTR strPwd)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lProOrUn, lType, strPwd);
		return result;
	}
	long UnProtectDoc(LPCTSTR strPwd)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strPwd);
		return result;
	}
	long AcceptAllRevisions()
	{
		long result;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetFieldValue(LPCTSTR strFieldName, LPCTSTR strValue, LPCTSTR strSheetName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strFieldName, strValue, strSheetName);
		return result;
	}
	CString GetFieldValue(LPCTSTR strFieldName, LPCTSTR strSheetName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strFieldName, strSheetName);
		return result;
	}
	long SetToolBarButton(long dwIndex, long dwID, short sControl)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I2 ;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_I4, (void*)&result, parms, dwIndex, dwID, sControl);
		return result;
	}
	long SaveAs(LPCTSTR strFileName, long dwFileFormat)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strFileName, dwFileFormat);
		return result;
	}
	long ShowDialog(long dwIndex)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_I4, (void*)&result, parms, dwIndex);
		return result;
	}
	long Save()
	{
		long result;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long PutSaved(long lSaved)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lSaved);
		return result;
	}
	long ExcProtectSharing(LPCTSTR strPassword, LPCTSTR strWriteResPassword, short bReadOnlyRecommended, LPCTSTR strSharingPassword)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I2 VTS_BSTR ;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strPassword, strWriteResPassword, bReadOnlyRecommended, strSharingPassword);
		return result;
	}
	long ExcUnprotectSharing(LPCTSTR strSharingPassword)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strSharingPassword);
		return result;
	}
	long InsertFile(LPCTSTR strFilePathName, short nCurPos)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I2 ;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strFilePathName, nCurPos);
		return result;
	}
	long DelLocalFile(LPCTSTR strFilePathName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strFilePathName);
		return result;
	}
	short CreateApp(LPCTSTR strAppName)
	{
		short result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_I2, (void*)&result, parms, strAppName);
		return result;
	}
	short OpenFileDlg()
	{
		short result;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	long CloseDoc(long blReqSaved)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, blReqSaved);
		return result;
	}
	short ConvertToAip(short nAddOriFile, short nSupport)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_I2, (void*)&result, parms, nAddOriFile, nSupport);
		return result;
	}
	CString GetTempFilePath()
	{
		CString result;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	short DeleteFile(LPCTSTR strFilePath)
	{
		short result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_I2, (void*)&result, parms, strFilePath);
		return result;
	}
	long HttpAddPostCurrFile(LPCTSTR strName, LPCTSTR strFilePath)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strName, strFilePath);
		return result;
	}
	long SetTrackRevisions(long lValue)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lValue);
		return result;
	}
	long SetCurrUserName(LPCTSTR strCurrUserName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strCurrUserName);
		return result;
	}
	long ShowRevisions(long nNewValue)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nNewValue);
		return result;
	}
	void Close()
	{
		InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long SetKeyCtrl(long lCtrl, long lChar, long lType)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x37, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lCtrl, lChar, lType);
		return result;
	}
	short SetToolBarButton2(VARIANT lIndex, VARIANT lID, VARIANT lControl)
	{
		short result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x38, DISPATCH_METHOD, VT_I2, (void*)&result, parms, &lIndex, &lID, &lControl);
		return result;
	}
	short SetCurrTime(LPCTSTR dateAndTime)
	{
		short result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_I2, (void*)&result, parms, dateAndTime);
		return result;
	}
	short SetValue(LPCTSTR strValue, LPCTSTR strName)
	{
		short result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x3a, DISPATCH_METHOD, VT_I2, (void*)&result, parms, strValue, strName);
		return result;
	}
	long SetDocVariable(LPCTSTR strVarName, LPCTSTR strValue, long lOpt)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x3b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strVarName, strValue, lOpt);
		return result;
	}
	long GetRevCount()
	{
		long result;
		InvokeHelper(0x3c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString GetRevInfo(long lIndex, long lType)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x3d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, lIndex, lType);
		return result;
	}
	long GetBookMarkCount()
	{
		long result;
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString GetBookMarkInfo(long lIndex, long lType)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, lIndex, lType);
		return result;
	}
	long BookMarkOpt(LPCTSTR strBookMarks, long lType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x40, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strBookMarks, lType);
		return result;
	}
	short ZipFile(LPCTSTR cSourceFile, LPCTSTR cAimFile, long wFileType, long bEnc)
	{
		short result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x41, DISPATCH_METHOD, VT_I2, (void*)&result, parms, cSourceFile, cAimFile, wFileType, bEnc);
		return result;
	}
	short AddMenu(LPCTSTR cMenuName, LPCTSTR cChildName, long iIndex, LPCTSTR cBindJSFun)
	{
		short result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR ;
		InvokeHelper(0x42, DISPATCH_METHOD, VT_I2, (void*)&result, parms, cMenuName, cChildName, iIndex, cBindJSFun);
		return result;
	}
	short DownLoadFile(LPCTSTR strHttpFileURL, LPCTSTR strLocalFilePath, LPCTSTR strTitle, LPCTSTR strFileType)
	{
		short result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x43, DISPATCH_METHOD, VT_I2, (void*)&result, parms, strHttpFileURL, strLocalFilePath, strTitle, strFileType);
		return result;
	}
	long SetSecurity(long lFlag)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x44, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lFlag);
		return result;
	}
	long AddSeal(LPCTSTR strSealPath, LPCTSTR strSealPostion, LPCTSTR strBMName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x45, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strSealPath, strSealPostion, strBMName);
		return result;
	}
	long VerifySealDoc(long lFlag)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x46, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lFlag);
		return result;
	}
	long DelSeal(long lFlag)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x47, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lFlag);
		return result;
	}
	short ListFilesInit(LPCTSTR strName)
	{
		short result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x48, DISPATCH_METHOD, VT_I2, (void*)&result, parms, strName);
		return result;
	}
	CString ListFiles(LPCTSTR strName, LPCTSTR strNameExit)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x49, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strName, strNameExit);
		return result;
	}
	short ListFilesRelease()
	{
		short result;
		InvokeHelper(0x4a, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	CString GetDirPath(LPCTSTR strDirExit)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x4b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strDirExit);
		return result;
	}
	short GetPageCount()
	{
		short result;
		InvokeHelper(0x4c, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	short CleanDoc()
	{
		short result;
		InvokeHelper(0x4d, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	long AcceptRevision(LPCTSTR strUserName, long nOpt)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x4e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strUserName, nOpt);
		return result;
	}
	long GetProtectType()
	{
		long result;
		InvokeHelper(0x4f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetSealCount(long nType)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x50, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nType);
		return result;
	}
	long SaveAsPDF(LPCTSTR strOriFilePath, LPCTSTR strSaveFilePath, long lType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x51, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strOriFilePath, strSaveFilePath, lType);
		return result;
	}
	long GetFileSize(LPCTSTR strFilePath)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x52, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strFilePath);
		return result;
	}
	CString GetDocVariable(LPCTSTR strName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x53, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strName);
		return result;
	}
	short GetSealNum(LPCTSTR strFilePath, short nType)
	{
		short result;
		static BYTE parms[] = VTS_BSTR VTS_I2 ;
		InvokeHelper(0x54, DISPATCH_METHOD, VT_I2, (void*)&result, parms, strFilePath, nType);
		return result;
	}
	long HideMenuAction(short shMenuMode, long lValue)
	{
		long result;
		static BYTE parms[] = VTS_I2 VTS_I4 ;
		InvokeHelper(0x55, DISPATCH_METHOD, VT_I4, (void*)&result, parms, shMenuMode, lValue);
		return result;
	}
	long ChangeTemplate(LPCTSTR cStartBM, LPCTSTR cEndBM, LPCTSTR cTemplatePath, LPCTSTR cTemplateStartBM, LPCTSTR cTemplateEndBM)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x56, DISPATCH_METHOD, VT_I4, (void*)&result, parms, cStartBM, cEndBM, cTemplatePath, cTemplateStartBM, cTemplateEndBM);
		return result;
	}
	short ReplaceText(LPCTSTR strSearchText, LPCTSTR strReplaceText, long lGradation)
	{
		short result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x57, DISPATCH_METHOD, VT_I2, (void*)&result, parms, strSearchText, strReplaceText, lGradation);
		return result;
	}
	long SetPageAs(LPCTSTR strLocalFile, long lPageNum, long lType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x58, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strLocalFile, lPageNum, lType);
		return result;
	}
	long GetBMPos(LPCTSTR strBMName, short lPosType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I2 ;
		InvokeHelper(0x59, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strBMName, lPosType);
		return result;
	}
	long LocalProtect(LPCTSTR strPosList, LPCTSTR strPwd, LPCTSTR strFuture)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x5a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strPosList, strPwd, strFuture);
		return result;
	}
	void UnActiveExcel()
	{
		InvokeHelper(0x5b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long HideMenuArea(LPCTSTR pcExcludeBar1, LPCTSTR pcExcludeBar2, LPCTSTR pcExcludeBar3, LPCTSTR pcExcludeBar4)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x5c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pcExcludeBar1, pcExcludeBar2, pcExcludeBar3, pcExcludeBar4);
		return result;
	}
	void SetCustomColour(long lType, long lColour)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x5d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lType, lColour);
	}
	long GetCustomColour(long lType)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lType);
		return result;
	}
	long SetCustomToolBtn(long lIndex, LPCTSTR pcBtnText)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x5f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lIndex, pcBtnText);
		return result;
	}
	VARIANT GetFileBinary(LPCTSTR strFilePath)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x60, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, strFilePath);
		return result;
	}
	long GetOcxVersion()
	{
		long result;
		InvokeHelper(0x61, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString GetFileBase64(LPCTSTR strFilePath, long dwExt)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x62, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strFilePath, dwExt);
		return result;
	}
	long SaveBinaryFileFromBase64(LPCTSTR strFilePath, LPCTSTR strBase64)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x63, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strFilePath, strBase64);
		return result;
	}
	long SetWindowText(LPCTSTR strText, long nType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x64, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strText, nType);
		return result;
	}
	VARIANT GetHttpPostFormatData(long dwFuture)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x65, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, dwFuture);
		return result;
	}
	long HideAreaWithoutResize(LPCTSTR strBKName, long blExtend, long blShow)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x66, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strBKName, blExtend, blShow);
		return result;
	}
	long SetDefDocType(LPCTSTR strDocType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x67, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDocType);
		return result;
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

long GetOptionFlag()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}
void SetOptionFlag(long propVal)
{
	SetProperty(0x2, VT_I4, propVal);
}
long GetShowToolBar()
{
	long result;
	GetProperty(0x3, VT_I4, (void*)&result);
	return result;
}
void SetShowToolBar(long propVal)
{
	SetProperty(0x3, VT_I4, propVal);
}
long GetlEventRet()
{
	long result;
	GetProperty(0x4, VT_I4, (void*)&result);
	return result;
}
void SetlEventRet(long propVal)
{
	SetProperty(0x4, VT_I4, propVal);
}
long GetFullScreen()
{
	long result;
	GetProperty(0x6, VT_I4, (void*)&result);
	return result;
}
void SetFullScreen(long propVal)
{
	SetProperty(0x6, VT_I4, propVal);
}
CString GetVersion()
{
	CString result;
	GetProperty(0x7, VT_BSTR, (void*)&result);
	return result;
}
void SetVersion(CString propVal)
{
	SetProperty(0x7, VT_BSTR, propVal);
}
long GetDocType()
{
	long result;
	GetProperty(0x8, VT_I4, (void*)&result);
	return result;
}
void SetDocType(long propVal)
{
	SetProperty(0x8, VT_I4, propVal);
}
CString GetAppVersion()
{
	CString result;
	GetProperty(0x9, VT_BSTR, (void*)&result);
	return result;
}
void SetAppVersion(CString propVal)
{
	SetProperty(0x9, VT_BSTR, propVal);
}
long GetIsModify()
{
	long result;
	GetProperty(0xa, VT_I4, (void*)&result);
	return result;
}
void SetIsModify(long propVal)
{
	SetProperty(0xa, VT_I4, propVal);
}
long GetlContinue()
{
	long result;
	GetProperty(0x5, VT_I4, (void*)&result);
	return result;
}
void SetlContinue(long propVal)
{
	SetProperty(0x5, VT_I4, propVal);
}
long GetIs2007()
{
	long result;
	GetProperty(0xb, VT_I4, (void*)&result);
	return result;
}
void SetIs2007(long propVal)
{
	SetProperty(0xb, VT_I4, propVal);
}
signed char GetReadOnly()
{
	signed char result;
	GetProperty(0x1, VT_I1, (void*)&result);
	return result;
}
void SetReadOnly(signed char propVal)
{
	SetProperty(0x1, VT_I1, propVal);
}


};
