//
// Created by harryqk on 7/17/22.
//

#include "SCPPSocketWin.h"
#include <iostream>
namespace scppsocket
{
    int SCPPSocketWin::Bind(int Port)
    {
        std::printf("this is win bind");
        return -1;
    }

    int SCPPSocketWin::Listen(int MaxConnect)
    {
        std::printf("this is win Listen");
        return -1;
    }

    SCPPSocketWin::SCPPSocketWin(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol)
            : SCPPSocket(AddressFamily, Type, Protocol)
    {

    }

    SCPPSocketWin::~SCPPSocketWin()
    {

    }

    int SCPPSocketWin::Connect(sockaddr *Address)
    {
        return 0;
    }

    SSocket SCPPSocketWin::Accept(sockaddr *Address)
    {
        return 0;
    }

    SockSSize_t SCPPSocketWin::Send(const char *Buf, SockSize_t Len, int Flag)
    {
        return 0;
    }

    SockSSize_t SCPPSocketWin::Read(char *Buf, SockSize_t Len, int Flag)
    {
        return 0;
    }

    bool SCPPSocketWin::ShutDown()
    {
        return false;
    }

    SCPPSocket *SCPPSocketWin::Clone(SSocket NewSocket, sockaddr_in NewPeerAddress)
    {
        return nullptr;
    }

}
