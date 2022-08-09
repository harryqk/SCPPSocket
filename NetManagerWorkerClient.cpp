//
// Created by harryqk on 8/8/22.
//

#include "NetManagerWorkerClient.h"
namespace scppsocket
{

    void NetManagerWorkerClient::SetOnClientMessageReadDelegate(OnClientMessageReadDelegate Delegate)
    {
        OnClientMessageRead = Delegate;
    }

    void NetManagerWorkerClient::SetOnConnectDelegate(OnConnectDelegate Delegate)
    {
        OnConnect  = Delegate;
    }

    NetManagerWorkerClient::NetManagerWorkerClient()
    {
        LenBuf = new char[4];
        ReadBuf = new char[1024];
        std::printf("construct NetManagerWorkerClient\n");
    }

    NetManagerWorkerClient::~NetManagerWorkerClient()
    {
        delete[] ReadBuf;
        ReadBuf = nullptr;
        delete[] LenBuf;
        LenBuf = nullptr;
        if(ConnectionToServer != nullptr)
        {
            delete ConnectionToServer;
            ConnectionToServer = nullptr;
        }


        std::printf("destruct NetManagerWorkerClient\n");
    }

    void NetManagerWorkerClient::DoWork()
    {
        std::printf("NetManagerWorkerClient DoWork\n");
    }

    void NetManagerWorkerClient::SendMessage(const char *Msg, int Len)
    {
        ConnectionToServer->Send(Msg, Len);
    }

    void NetManagerWorkerClient::StopWork()
    {
        std::printf("NetManagerWorkerClient StopWork\n");
    }
}