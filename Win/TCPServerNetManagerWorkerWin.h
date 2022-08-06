//
// Created by WIN10 on 2022/8/1.
//

#ifndef SCPPSOCKET_TCPSERVERNETMANAGERWORKERWIN_H
#define SCPPSOCKET_TCPSERVERNETMANAGERWORKERWIN_H
#include "../NetManagerWorker.h"
#include <list>
#include "../SocketUtil.h"
namespace scppsocket
{
    class TCPServerNetManagerWorkerWin:public NetManagerWorker
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
        TCPServerNetManagerWorkerWin();
        virtual ~TCPServerNetManagerWorkerWin() override;
        int GetMacConnection() const;
        virtual void DoWork() override;
        void SetMacConnection(int macConnection);
        virtual void SendMessage(const char *Msg, int Len) override;
        virtual void StopWork() override;
    };

}


#endif //SCPPSOCKET_TCPSERVERNETMANAGERWORKERWIN_H
