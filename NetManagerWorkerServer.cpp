//
// Created by harryqk on 8/8/22.
//

#include "NetManagerWorkerServer.h"
namespace scppsocket
{

    NetManagerWorkerServer::NetManagerWorkerServer()
    {
        LenBuf = new char[4];
        ReadBuf = new char[1024];
        std::printf("construct NetManagerWorkerServer\n");
    }

    NetManagerWorkerServer::~NetManagerWorkerServer()
    {
        delete LenBuf;
        LenBuf = nullptr;
        delete ReadBuf;
        ReadBuf = nullptr;
        while(!ConnectionsToClient.empty()){
            Connection* Conn = ConnectionsToClient.front();
            ConnectionsToClient.pop_front();
            delete Conn;
            Conn = nullptr;
        }
        std::printf("destruct NetManagerWorkerServer\n");
    }

    void NetManagerWorkerServer::SetOnBindDelegate(OnBindDelegate Delegate)
    {
        OnBind = Delegate;
    }

    void NetManagerWorkerServer::SetOnAcceptDelegate(OnAcceptDelegate Delegate)
    {
        OnAccept = Delegate;
    }

    void NetManagerWorkerServer::SetOnRemoveClientDelegate(OnRemoveClientDelegate Delegate)
    {
        OnRemoveClient = Delegate;
    }

    void NetManagerWorkerServer::SetOnServerMessageReadDelegate(OnServerMessageReadDelegate Delegate)
    {
        OnServerMessageRead = Delegate;
    }

    SCPPSocket *NetManagerWorkerServer::GetLocal() const
    {
        return Local;
    }

    void NetManagerWorkerServer::SetLocal(SCPPSocket *local)
    {
        Local = local;
    }

    int NetManagerWorkerServer::GetMaxConnection() const
    {
        return MaxConnection;
    }

    void NetManagerWorkerServer::DoWork()
    {

    }

    void NetManagerWorkerServer::SetMaxConnection(int maxConnection)
    {
        MaxConnection = maxConnection;
    }

    void NetManagerWorkerServer::StopWork()
    {

    }
}