//
// Created by harryqk on 7/17/22.
//

#include "SCPPSocketFactoryWin.h"
#include "SCPPSocketWin.h"
#include "SCPPSocket.h"
namespace scppsocket
{
    SCPPSocket* SCPPSocketFactoryWin::CreateSocket(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol)
    {
        //SCPPSocketWin* SocketMac = new SCPPSocketWin(AddressFamily, Type, Protocol);
        return nullptr;
    }
}