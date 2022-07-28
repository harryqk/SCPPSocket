//
// Created by harryqk on 7/17/22.
//

#include "NetManager.h"
#include <iostream>
#include "SCPPSocketFactoryMac.h"
#include "SCPPSocket.h"
#include "TCPConnection.h"
#include "SocketUtil.h"
namespace scppsocket
{
    NetManager::NetManager()
    {
        std::cout << "Construct NetManager" << std::endl;
    }

    NetManager::~NetManager()
    {
        std::cout << "Destruct NetManager" << std::endl;
    }


    void NetManager::StartTCPClient(const char* Address, int Port)
    {
        SCPPSocketFactory* Factory;
#ifdef _WIN32
        Factory = new SCPPSocketFactoryWin();
#elif __APPLE__
        Factory = new SCPPSocketFactoryMac();
#elif __ANDROID__
#endif
        SCPPSocket* Socket = Factory->CreateSocket(SocketAddressFamily::IPv4, SocketType::SOCKTYPE_Streaming, SocketProtocol::TCP);

        //connect
        sockaddr_in ServerAddress = Factory->CreateAddress(Address, Port);
        Socket->SetPeerAddress(ServerAddress);
        //set NonBlockMode
        int ret = Socket->SetNonBlockMode(true);
        if(ret != SocketBlockMode::NonBlock)
        {
            std::printf("Set NonBlock mode fail\n");
            return;
        }

        Connection* ConnectionToServer = new TCPConnection(Socket);
        ClientWorker = Factory->CreateTCPClientNetMangerWorker(ConnectionToServer);
        ClientWorker->SetIsWorking(true);
        std::thread thd([&]()
                        {
                            ClientWorker->DoWork();
                        });
        thd.detach();
        delete Factory;
        Factory = nullptr;
    }

    void NetManager::StopTCPCServer()
    {
        if(ServerWorker != nullptr)
        {
            ServerWorker->SetIsWorking(false);
            ServerWorker->StopWork();
            delete ServerWorker;
        }
    }

    void NetManager::StopTCPClient()
    {
        if(ClientWorker != nullptr)
        {
            ClientWorker->SetIsWorking(false);
            ClientWorker->StopWork();
            delete ClientWorker;
        }
    }



    void NetManager::TCPClientSendMessage(const char *Msg, int Len)
    {
        byte* bytes = new byte[4];
        SocketUtil::IntToByte(Len, bytes);
        char* sendBuff = new char[Len + 4];//4 is byte length of data
        memcpy(sendBuff, bytes, 4);
        memcpy(sendBuff + 4, Msg, Len);
        ClientWorker->SendMessage(sendBuff, Len + 4);
    }

    void NetManager::StartTCPClientSubThread(const char* Address, int Port)
    {

    }

    bool NetManager::StartTCPServer(int Port, int MaxConnection)
    {
        SCPPSocketFactory* Factory;
#ifdef _WIN32
        Factory = new SCPPSocketFactoryWin();
#elif __APPLE__
        Factory = new SCPPSocketFactoryMac();
#elif __ANDROID__
#endif
        SCPPSocket* Socket = Factory->CreateSocket(SocketAddressFamily::IPv4, SocketType::SOCKTYPE_Streaming, SocketProtocol::TCP);

        //set NonBlockMode
        bool ret = Socket->SetNonBlockMode(true);
        if(!ret)
        {
            std::printf("Set NonBlock mode fail");
            return false;
        }
        //bind
        int result;
        result = Socket->Bind(Port);
        if(result == SOCKET_ERROR)
        {
            std::printf("Bind fail");
            return false;
        }
        //listen;
        result = Socket->Listen(MaxConnection);
        if(result == SOCKET_ERROR)
        {
            std::printf("Listen fail");
            return false;
        }
        ServerWorker = Factory->CreateTCPServerNetMangerWorker(Socket);
        ServerWorker->SetIsWorking(true);
        std::thread thd([&]()
                        {
                            ServerWorker->DoWork();
                        });

        thd.detach();
        delete Factory;
        Factory = nullptr;
        return true;
    }
}



