#include "pch.h"
#include "CClientSock.h"
#include "Practice13a.h"



void CClientSock::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CPractice13aApp*)AfxGetApp())->CloseChild();

	CAsyncSocket::OnClose(nErrorCode);
}


void CClientSock::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CPractice13aApp*)AfxGetApp())->ReceiveData();

	CAsyncSocket::OnReceive(nErrorCode);
}
