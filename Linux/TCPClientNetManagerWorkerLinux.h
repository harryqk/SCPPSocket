//
// Created by harryqk on 7/21/22.
//

#ifndef SCPPSOCKET_TCPCLIENTNETMANAGERWORKERMAC_H
#define SCPPSOCKET_TCPCLIENTNETMANAGERWORKERMAC_H

#include "../NetManagerWorkerClient.h"
namespace scppsocket
{

    class TCPClientNetManagerWorkerLinux:public NetManagerWorkerClient
    {
    public:
        TCPClientNetManagerWorkerLinux();
        virtual ~TCPClientNetManagerWorkerLinux() override;
    private:
        int HandleConnect();
        void HandleRead();
        fd_set readfds;
        fd_set testfds;

    public:
        virtual void DoWork() override;
        virtual void SendMessage(const char *Msg, int Len) override;
        virtual void StopWork() override;

    };

}



#endif //SCPPSOCKET_TCPCLIENTNETMANAGERWORKERMAC_H
