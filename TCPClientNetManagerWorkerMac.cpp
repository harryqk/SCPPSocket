//
// Created by harryqk on 7/21/22.
//

#include "TCPClientNetManagerWorkerMac.h"
#include "SocketUtil.h"
#include <sys/select.h>
namespace scppsocket
{

    void TCPClientNetManagerWorkerMac::DoWork()
    {
        int nread;
        int fd = ConnectionToServer->GetSSock()->GetFileDescriptor();
        int ret = HandleConnect();
        int result;
        if(ret == SOCKET_ERROR)
        {
            ConnectionToServer->GetSSock()->Close();
            return;
        }
        FD_ZERO(&readfds);
        //Add client fd to set
        FD_SET(fd, &readfds);
        while(IsWorking)
        {
            //Copy readfds to testfds, select will modify testfds
            testfds = readfds;
            printf("client waiting\n");

            //Block until certain fd readable or error return, FD_SETSIZE is max system fd value
            result = select(FD_SETSIZE, &testfds, (fd_set *) nullptr,(fd_set *)nullptr, (struct timeval *) nullptr);


            if(result < 1)
            {
                printf("mac client select return errno=%d\n", errno);
                perror("mac client select return error");
                ConnectionToServer->GetSSock()->Close();
                printf("client close socket on fd %d\n", fd);
                break;
            }

            if(FD_ISSET(fd, &testfds))
            {
                ioctl(fd, FIONREAD, &nread);

                //Server shutdown, close client
                if(nread == 0)
                {
                    ConnectionToServer->GetSSock()->Close();
                    printf("client close socket on fd %d\n", fd);
                    break;
                    //close(fd);
                    //FD_CLR(fd, &readfds);
                    //printf("removing client on fd %d\n", fd);
                }
                else
                {
                    ConnectionToServer->Read(LenBuf, 4);
                    int len = SocketUtil::BytesToInt((byte *)LenBuf);
                    ConnectionToServer->Read(ReadBuf, len);
                    char* msg = new char[len];
                    memcpy(msg, ReadBuf, len);
                    printf("client read  %d\n", len);
                    printf("client read  %s\n", msg);
                }
            }
        }

    }

    void TCPClientNetManagerWorkerMac::SendMessage(const char *Msg, int Len)
    {
        ConnectionToServer->Send(Msg, Len);
    }

    TCPClientNetManagerWorkerMac::TCPClientNetManagerWorkerMac()
    {
        LenBuf = new char[4];
        ReadBuf = new char[1024];
        std::printf("construct TCPClientNetManagerWorkerMac\n");
    }

    TCPClientNetManagerWorkerMac::~TCPClientNetManagerWorkerMac()
    {

        std::printf("destruct TCPClientNetManagerWorkerMac\n");
    }


    void TCPClientNetManagerWorkerMac::HandleRead()
    {

    }

    int TCPClientNetManagerWorkerMac::HandleConnect()
    {
        int client_fd;
        int result;
        int ret = SOCKET_ERROR;
        SCPPSocket* Local = ConnectionToServer->GetSSock();
        client_fd = Local->GetFileDescriptor();

        result = Local->Connect((sockaddr*)&Local->GetPeerAddress());
        if (result != 0 )
        {
            if(errno != EINPROGRESS)
                printf("connect error :%s\n",strerror(errno));
            else
            {
                struct timeval tm = {2, 0};
                fd_set wset,rset;
                FD_ZERO(&wset);
                FD_ZERO(&rset);
                FD_SET(client_fd,&wset);
                FD_SET(client_fd,&rset);
                long t1 = time(nullptr);
                int res = select(client_fd+1,&rset,&wset,nullptr,&tm);
                long t2 = time(nullptr);
                printf("interval time: %ld\n", t2 - t1);
                if(res < 0)
                {
                    printf("network error in connect\n");
                }
                else if(res == 0)
                {
                    printf("connect time out\n");
                }
                else if (1 == res)
                {
                    if(FD_ISSET(client_fd,&wset))
                    {
                        printf("connect succeed.\n");
                        //Local->SetFileDescriptor(result);
                        ret = 0;
                    }
                    else
                    {
                        printf("other error when select:%s\n",strerror(errno));
                    }
                }
            }
        }
        return ret;

    }

    void TCPClientNetManagerWorkerMac::StopWork()
    {
        delete ReadBuf;
        ReadBuf = nullptr;
        delete LenBuf;
        LenBuf = nullptr;
        ConnectionToServer->GetSSock()->ShutDown();
        ConnectionToServer->GetSSock()->Close();
        delete ConnectionToServer;
        ConnectionToServer = nullptr;
        std::printf("TCPClientNetManagerWorkerMac StopWork\n");
    }
}