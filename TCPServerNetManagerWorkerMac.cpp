//
// Created by harryqk on 7/21/22.
//

#include "TCPServerNetManagerWorkerMac.h"
#include "TCPConnection.h"
#include <iostream>
namespace scppsocket
{
    void TCPServerNetManagerWorkerMac::DoWork()
    {
        int server_sockfd;
        int result;
        server_sockfd = Local->GetFileDescriptor();
        FD_ZERO(&readfds);
        //Add server fd to set
        FD_SET(server_sockfd, &readfds);
        while(IsWorking)
        {
            //Copy readfds to testfds, select will modify testfds
            testfds = readfds;
            printf("server waiting\n");

            //Block until certain fd readable or error return, FD_SETSIZE is max system fd value
            result = select(FD_SETSIZE, &testfds, (fd_set *) nullptr,(fd_set *)nullptr, (struct timeval *) nullptr);
            if(result < 1)
            {
                printf("mac server select return errno=%d\n", errno);
                perror("mac server select return error");
                Local->Close();
                break;
            }

            if(FD_ISSET(server_sockfd, &testfds))
            {
                HandleAccept();
            }
            else
            {
                HandleRead();
            }
        }
        printf("server finish\n");
    }

    int TCPServerNetManagerWorkerMac::GetMacConnection() const
    {
        return MacConnection;
    }

    void TCPServerNetManagerWorkerMac::SetMacConnection(int macConnection)
    {
        MacConnection = macConnection;
    }

    void TCPServerNetManagerWorkerMac::HandleAccept()
    {
        int client_sockfd;
        struct sockaddr_in client_address;
        client_sockfd = Local->Accept((struct sockaddr *)&client_address);
        SCPPSocket* NewSock = Local->Clone(client_sockfd, client_address);
        Connection* Conn = new TCPConnection(NewSock);
        ConnectionsToClient.push_back(Conn);
        FD_SET(client_sockfd, &readfds);
        printf("adding client on fd %d\n", client_sockfd);
    }

    void TCPServerNetManagerWorkerMac::HandleRead()
    {
        int nread;

        std::list<Connection*>::iterator it = ConnectionsToClient.begin();
        while (it != ConnectionsToClient.end())
        {
            Connection* conn = *it;
            SSocket fd = conn->GetSSock()->GetFileDescriptor();
            if(FD_ISSET(fd,&testfds))
            {
                ioctl(fd, FIONREAD, &nread);

                //Client shutdown, close socket of that client, remove this connection
                if(nread ==0)
                {
                    conn->GetSSock()->Close();
                    //Clear select readfds of this client
                    FD_CLR(fd, &readfds);
                    printf("removing client on fd %d\n", fd);
                    ConnectionsToClient.erase(it++);
                    delete conn;
                    conn = nullptr;

                }
                else
                {
                    conn->Read(LenBuf, 4);
                    int len = SocketUtil::BytesToInt((byte *)LenBuf);
                    conn->Read(ReadBuf, len);
                    char* msg = new char[len];
                    memcpy(msg, ReadBuf, len);
                    std::cout << len << std::endl;
                    std::cout << msg << std::endl;
                    it++;
                    printf("server read  %s\n", msg);
                }
            } else
            {
                it++;
            }
        }
    }

    TCPServerNetManagerWorkerMac::TCPServerNetManagerWorkerMac()
    {
        LenBuf = new char[4];
        ReadBuf = new char[1024];
        std::printf("construct TCPServerNetManagerWorkerMac\n");
    }

    TCPServerNetManagerWorkerMac::~TCPServerNetManagerWorkerMac()
    {
        if(Local != nullptr)
        {
            delete Local;
            Local = nullptr;
        }
        std::printf("destruct TCPServerNetManagerWorkerMac\n");
    }

    void TCPServerNetManagerWorkerMac::SendMessage(const char *Msg, int Len)
    {

    }

    SCPPSocket *scppsocket::TCPServerNetManagerWorkerMac::GetLocal() const
    {
        return Local;
    }

    void TCPServerNetManagerWorkerMac::SetLocal(scppsocket::SCPPSocket *local)
    {
        Local = local;
    }

    void TCPServerNetManagerWorkerMac::StopWork()
    {
        delete LenBuf;
        LenBuf = nullptr;
        delete ReadBuf;
        ReadBuf = nullptr;
        while(!ConnectionsToClient.empty()){
            Connection* Conn = ConnectionsToClient.front();
            ConnectionsToClient.pop_front();
            if(Conn->GetSSock())
            {
                Conn->GetSSock()->Close();
            }
            delete Conn;
            Conn = nullptr;
        }
        if(Local != nullptr)
        {
            Local->ShutDown();
            Local->Close();
        }
        std::printf("TCPServerNetManagerWorkerMac StopWork\n");
    }
}


