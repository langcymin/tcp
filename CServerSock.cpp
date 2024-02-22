#include "pch.h"
#include "CServerSock.h"
#include "Practice13a.h"


void CServerSock::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	((CPractice13aApp*)AfxGetApp())->Accept();


	CAsyncSocket::OnAccept(nErrorCode);
}
