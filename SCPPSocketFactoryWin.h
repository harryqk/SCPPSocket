//
// Created by harryqk on 7/17/22.
//

#ifndef SCPPSOCKET_SCPPSOCKETFACTORYWIN_H
#define SCPPSOCKET_SCPPSOCKETFACTORYWIN_H
#include "SCPPSocketFactory.h"

namespace scppsocket
{
    class SCPPSocketFactoryWin : public SCPPSocketFactory{
        virtual SCPPSocket* CreateSocket(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol) override;
    };


}



#endif //SCPPSOCKET_SCPPSOCKETFACTORYWIN_H
