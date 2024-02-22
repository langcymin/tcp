
// Practice13a.h: PROJECT_NAME 애플리케이션에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.
#include "CServerSock.h"
#include "CClientSock.h"


// CPractice13aApp:
// 이 클래스의 구현에 대해서는 Practice13a.cpp을(를) 참조하세요.
//

class CPractice13aApp : public CWinApp
{
public:
	CPractice13aApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.



	DECLARE_MESSAGE_MAP()

public:
	CServerSock* m_pServer;    //CServerSock형 변수를 포인터로 선언.
	CClientSock* m_pClient;    //CClientSock형 변수를 포인터로 선언.
	void InitServer();
	void Accept();
	void CleanUp();
	void Connect(CString strIP);
	void ReceiveData();
	void SendData(CString strData);
	void CloseChild();

};

extern CPractice13aApp theApp;
