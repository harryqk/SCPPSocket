//
// Created by harryqk on 7/17/22.
//

#ifndef SCPPSOCKET_NETMANAGER_H
#define SCPPSOCKET_NETMANAGER_H
#include "NetManagerWorker.h"
#include <list>
#include <thread>
namespace scppsocket
{
    class NetManager {
    public:

        bool StartTCPServer(int Port, int MaxConnection);
        void StopTCPCServer();

        void StartTCPClient(const char* Address, int Port);
        void StopTCPClient();
        void TCPClientSendMessage(const char* Msg, int Len);
        void Clear();
        NetManager();
        ~NetManager();
    private:

        NetManagerWorker* ClientWorker;
        NetManagerWorker* ServerWorker;
        SCPPSocket* Local;
        void StartTCPClientSubThread(const char* Address, int Port);
        //std::list<Connection*> ConnectionsToClient;
        //Connection* ConnectionToServer;



    };

}


#endif //SCPPSOCKET_NETMANAGER_H
