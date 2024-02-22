#pragma once
#include <afxsock.h>
class CServerSock :
    public CAsyncSocket
{
public:
    virtual void OnAccept(int nErrorCode);
};

