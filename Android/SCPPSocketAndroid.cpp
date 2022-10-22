//
// Created by harryqk on 7/17/22.
//

#include "SCPPSocketAndroid.h"
#include <iostream>
#include <fcntl.h>
namespace scppsocket
{
    SCPPSocketAndroid::SCPPSocketAndroid(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol) : SCPPSocket(AddressFamily, Type, Protocol)
    {
        std::printf("this is SCPPSocketAndroid Construct\n");
        FileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
        if (FileDescriptor == SOCKET_ERROR) {

            int error = errno;
            //perror("SCPPSocketAndroid fail ");

        }
    }

    SCPPSocketAndroid::~SCPPSocketAndroid()
    {
        std::printf("this is SCPPSocketAndroid Destruct\n");
    }

    int SCPPSocketAndroid::Bind(int Port)
    {
        std::printf("this is Android bind\n");

        struct sockaddr_in Address;
        //memset(&Address, 0, sizeof(Address));
        Address.sin_family = AF_INET;  //
        Address.sin_addr.s_addr = INADDR_ANY;
        Address.sin_port = htons(Port);
        LocalAddress = Address;
        int ret = bind(FileDescriptor, (struct sockaddr*)&Address, sizeof(Address));
        if(ret == SOCKET_ERROR)
        {
            //printf("this is mac Bind fail, errno=%d\n", errno);
            perror("Android Bind fail");
        }
        else
        {
            printf("this is Android Bind success\n");
        }
        return ret;
    }

    int SCPPSocketAndroid::Listen(int MaxConnect)
    {
        printf("this is Android Listen\n");
        int ret = listen(FileDescriptor, MaxConnect);
        if(ret < 0)
        {
            //printf("this is mac Listen fail, errno=%d\n", errno);
            perror("Android Listen fail");

        }
        else
        {
            printf("this is Android Listen success\n");
        }

        return ret;
    }

    int SCPPSocketAndroid::Connect(sockaddr *Address)
    {
        int ret = connect(FileDescriptor, Address, sizeof(sockaddr));
        if (ret == SOCKET_ERROR)
        {
            //std::printf("Mac Connect Error\n");
            perror("Android Connect Error");
            //close(FileDescriptor);
        }
        else {
            std::printf("Android Connect Success\n");
        }
        return ret;
    }

    SSocket SCPPSocketAndroid::Accept(sockaddr *Address)
    {
        SockLen_t Len = sizeof(struct  sockaddr);
        SSocket NewSock = accept(FileDescriptor, Address, &Len);
        if (NewSock == SOCKET_ERROR)
        {
            //printf("Mac Accept fail, errno=%d\n", errno);
            perror("Android Accept fail");
        }
        else {
            std::printf("Android Accept Success\n");
        }
        return NewSock;
    }

    SockSSize_t SCPPSocketAndroid::Send(const char *Buf, SockSize_t Len, int Flag)
    {
        std::printf("this is Android Send\n");
        SockSSize_t Sent = send(FileDescriptor, Buf, Len, Flag);
        return Sent;
    }

    SockSSize_t SCPPSocketAndroid::Read(char *Buf, SockSize_t Len, int Flag)
    {
        std::printf("this is Android Recv\n");
        SockSSize_t Read = recv(FileDescriptor, Buf, Len, Flag);
        return Read;
    }

    int SCPPSocketAndroid::SetNonBlockMode(bool NonBlock)
    {
        int flags = 0;

        flags = fcntl(FileDescriptor, F_GETFL, 0);
        if (SOCKET_ERROR == flags)
        {
            //printf("get sockfd flag -1, errno=%d\n", errno);
            perror("Android SetNonBlockMode error");
            BlockMode = SocketBlockMode::Unknown;
            return BlockMode;
        }

        if (NonBlock)
        {
            if (fcntl(FileDescriptor, F_SETFL, flags | O_NONBLOCK) == SOCKET_ERROR)
            {
                //printf("set sockfd nonblock -1, errno=%d\n", errno);
                perror("Android SetNonBlockMode error");
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
                perror("Android SetNonBlockMode error");
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

    SCPPSocketAndroid::SCPPSocketAndroid()
    {
        std::printf("SCPPSocketAndroid default construct\n");
    }

    bool SCPPSocketAndroid::Close()
    {
        int ret;
        try {
            ret = close(FileDescriptor);
        }
        catch(std::exception e)
        {
            printf("Android close exception=%s\n", e.what());
        }
        if(ret == SOCKET_ERROR)
        {
            //printf("mac close errno=%d\n", errno);
            perror("Android close error");
            return false;
        } else
        {
            printf("Android close success\n");
            return true;
        }
    }

    bool SCPPSocketAndroid::ShutDown()
    {
        int ret;
        try {
            ret = shutdown(FileDescriptor, 2);
        }
        catch(std::exception e)
        {
            printf("Android shutdown exception=%s\n", e.what());
        }
        if(ret == SOCKET_ERROR)
        {
            //printf("mac shut down errno=%d\n", errno);
            perror("Android shut down error");
            return false;
        } else
        {
            printf("Android shut down success\n");
            return true;
        }
    }

    SCPPSocket *SCPPSocketAndroid::Clone(SSocket NewSocket, sockaddr_in NewPeerAddress)
    {
        SCPPSocketAndroid* Android = new SCPPSocketAndroid(AddressFamily, Type, Protocol);
        Android->SetPeerAddress(NewPeerAddress);
        Android->SetFileDescriptor(NewSocket);
        return Android;
    }
}
