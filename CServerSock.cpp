#include "pch.h"
#include "CServerSock.h"
#include "Practice13a.h"


void CServerSock::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CPractice13aApp*)AfxGetApp())->Accept();


	CAsyncSocket::OnAccept(nErrorCode);
}
