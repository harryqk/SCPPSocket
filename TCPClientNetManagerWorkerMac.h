//
// Created by harryqk on 7/21/22.
//

#ifndef SCPPSOCKET_TCPCLIENTNETMANAGERWORKERMAC_H
#define SCPPSOCKET_TCPCLIENTNETMANAGERWORKERMAC_H
#include "NetManagerWorker.h"
namespace scppsocket
{

    class TCPClientNetManagerWorkerMac:public NetManagerWorker
    {
    public:
        TCPClientNetManagerWorkerMac();
        virtual ~TCPClientNetManagerWorkerMac() override;
    private:
        int HandleConnect();
        void HandleRead();
        fd_set readfds;
        fd_set testfds;
        char* LenBuf;
        char* ReadBuf;
    public:
        Connection *ConnectionToServer;
        virtual void DoWork() override;
        virtual void SendMessage(const char *Msg, int Len) override;
        virtual void StopWork() override;

    };

}



#endif //SCPPSOCKET_TCPCLIENTNETMANAGERWORKERMAC_H
