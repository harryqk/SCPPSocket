//
// Created by harryqk on 7/21/22.
//

#ifndef SCPPSOCKET_TCPSERVERNETMANAGERWORKERMAC_H
#define SCPPSOCKET_TCPSERVERNETMANAGERWORKERMAC_H
#include "NetManagerWorker.h"
#include <list>
#include "SocketUtil.h"
namespace scppsocket
{

    class TCPServerNetManagerWorkerMac:public NetManagerWorker
    {
        std::list<Connection*> ConnectionsToClient;
        SCPPSocket* Local;
    public:
        SCPPSocket *GetLocal() const;

        void SetLocal(SCPPSocket *local);

    private:
        int MacConnection;
        void HandleAccept();
        void HandleRead();
        fd_set readfds;
        fd_set testfds;
        char* LenBuf;
        char* ReadBuf;
    public:
        TCPServerNetManagerWorkerMac();
        virtual ~TCPServerNetManagerWorkerMac() override;
        int GetMacConnection() const;
        virtual void DoWork() override;
        void SetMacConnection(int macConnection);
        virtual void SendMessage(const char *Msg, int Len) override;
        virtual void StopWork() override;
    };

}


#endif //SCPPSOCKET_TCPSERVERNETMANAGERWORKERMAC_H
