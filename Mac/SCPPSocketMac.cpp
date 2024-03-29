//
// Created by harryqk on 7/17/22.
//

#include "SCPPSocketMac.h"
#include <iostream>
#include <fcntl.h>
namespace scppsocket
{
    SCPPSocketMac::SCPPSocketMac(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol) : SCPPSocket(AddressFamily, Type, Protocol)
    {
        std::printf("this is SCPPSocketMac Construct\n");
        FileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
        if (FileDescriptor == SOCKET_ERROR) {
            perror("SCPPSocketMac fail ");
        }
    }

    SCPPSocketMac::~SCPPSocketMac()
    {
        std::printf("this is SCPPSocketMac Destruct\n");
    }

    int SCPPSocketMac::Bind(int Port)
    {
        std::printf("this is mac bind\n");

        struct sockaddr_in Address;
        memset(&Address, 0, sizeof(Address));
        Address.sin_family = AF_INET;  //
        Address.sin_addr.s_addr = INADDR_ANY;
        Address.sin_port = htons(Port);
        LocalAddress = Address;
        int ret = bind(FileDescriptor, (struct sockaddr*)&Address, sizeof(Address));
        if(ret == SOCKET_ERROR)
        {
            //printf("this is mac Bind fail, errno=%d\n", errno);
            perror("mac Bind fail");
        }
        else
        {
            printf("this is mac Bind success\n");
        }
        return ret;
    }

    int SCPPSocketMac::Listen(int MaxConnect)
    {
        printf("this is mac Listen\n");
        int ret = listen(FileDescriptor, MaxConnect);
        if(ret < 0)
        {
            //printf("this is mac Listen fail, errno=%d\n", errno);
            perror("mac Listen fail");

        }
        else
        {
            printf("this is mac Listen success\n");
        }

        return ret;
    }

    int SCPPSocketMac::Connect(sockaddr *Address)
    {

        int ret = connect(FileDescriptor, Address, sizeof(sockaddr));
        if (ret == SOCKET_ERROR)
        {
            //std::printf("Mac Connect Error\n");
            perror("Mac Connect Error");
            //close(FileDescriptor);
        }
        else {
            std::printf("Mac Connect Success\n");
        }
        return ret;
    }

    SSocket SCPPSocketMac::Accept(sockaddr *Address)
    {
        SockLen_t Len = sizeof(struct  sockaddr);
        SSocket NewSock = accept(FileDescriptor, Address, &Len);
        if (NewSock == SOCKET_ERROR)
        {
            //printf("Mac Accept fail, errno=%d\n", errno);
            perror("Mac Accept fail");
        }
        else {
            std::printf("Mac Accept Success\n");
        }
        return NewSock;
    }

    SockSSize_t SCPPSocketMac::Send(const char *Buf, SockSize_t Len, int Flag)
    {
        std::printf("this is mac Send\n");
        SockSSize_t Sent = send(FileDescriptor, Buf, Len, Flag);
        return Sent;
    }

    SockSSize_t SCPPSocketMac::Read(char *Buf, SockSize_t Len, int Flag)
    {
        std::printf("this is mac Recv\n");
        SockSSize_t Read = recv(FileDescriptor, Buf, Len, Flag);
        return Read;
    }

    int SCPPSocketMac::SetNonBlockMode(bool NonBlock)
    {
        int flags = 0;

        flags = fcntl(FileDescriptor, F_GETFL, 0);
        if (SOCKET_ERROR == flags)
        {
            //printf("get sockfd flag -1, errno=%d\n", errno);
            perror("mac SetNonBlockMode error");
            BlockMode = SocketBlockMode::Unknown;
            return BlockMode;
        }

        if (NonBlock)
        {
            if (fcntl(FileDescriptor, F_SETFL, flags | O_NONBLOCK) == SOCKET_ERROR)
            {
                //printf("set sockfd nonblock -1, errno=%d\n", errno);
                perror("Mac SetNonBlockMode error");
                BlockMode = SocketBlockMode::Unknown;
                return BlockMode;
            }
            else
            {
                BlockMode = SocketBlockMode::NonBlock;
            }
        }
        else
        {
            if (fcntl(FileDescriptor, F_SETFL, flags & (~O_NONBLOCK)) == SOCKET_ERROR)
            {
                //printf("set sockfd nonblock -1, errno=%d\n", errno);
                perror("mac SetNonBlockMode error");
                BlockMode = SocketBlockMode::Unknown;
                return BlockMode;
            }
            else
            {
                BlockMode = SocketBlockMode::Block;
            }
        }

        return BlockMode;


    }

    SCPPSocketMac::SCPPSocketMac()
    {
        std::printf("SCPPSocketMac default construct\n");
    }

    bool SCPPSocketMac::Close()
    {
        int ret;
        try {
            ret = close(FileDescriptor);
        }
        catch(std::exception e)
        {
            printf("mac close exception=%s\n", e.what());
        }
        if(ret == SOCKET_ERROR)
        {
            //printf("mac close errno=%d\n", errno);
            perror("Mac close error");
            return false;
        } else
        {
            printf("mac close success\n");
            return true;
        }
    }

    bool SCPPSocketMac::ShutDown()
    {
        int ret;
        try {
            ret = shutdown(FileDescriptor, 2);
        }
        catch(std::exception e)
        {
            printf("mac shutdown exception=%s\n", e.what());
        }
        if(ret == SOCKET_ERROR)
        {
            //printf("mac shut down errno=%d\n", errno);
            perror("Mac shut down error");
            return false;
        } else
        {
            printf("mac shut down success\n");
            return true;
        }
    }

    SCPPSocket *SCPPSocketMac::Clone(SSocket NewSocket, sockaddr_in NewPeerAddress)
    {
        SCPPSocketMac* Mac = new SCPPSocketMac(AddressFamily, Type, Protocol);
        Mac->SetPeerAddress(NewPeerAddress);
        Mac->SetFileDescriptor(NewSocket);
        return Mac;
    }
}
