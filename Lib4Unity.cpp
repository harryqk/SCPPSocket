#include "Lib4Unity.h"

#include <iostream>
#include "NetManager.h"

namespace scppsocket
{


    void hello()
    {
    #ifdef _WIN32
        std::cout << "Hello, World win!" << std::endl;
    #elif  __linux__
        std::cout << "Hello, World linux!" << std::endl;
    #elif __APPLE__
        std::cout << "Hello, World mac!" << std::endl;
    #elif __ANDROID__
        std::cout << "Hello, World android!" << std::endl;
    #endif

    }

    int Accept()
    {
    #ifdef _WIN32
        return 0;
    #elif  __linux__
        return 1;
    #elif __APPLE__
        return 2;
    #elif __ANDROID__
        return 3;
    #endif

    }

    NetManager *GetMgr()
    {
        NetManager* Mgr = new NetManager;
        return Mgr;
    }

    void StartClient(NetManager *Mgr, const char *Address, int Port)
    {
        if(Mgr != nullptr)
        {
            Mgr->StartTCPClient(Address, Port);
        }

    }

    void StartServer(NetManager *Mgr, int Port, int MaxConnection)
    {
        if(Mgr != nullptr)
        {
            Mgr->StartTCPServer(Port, MaxConnection);
        }

    }

    void StopClient(NetManager *Mgr)
    {
        if(Mgr != nullptr)
        {
            Mgr->StopTCPClient();
        }
    }

    void StopServer(NetManager *Mgr)
    {
        if(Mgr != nullptr)
        {
            Mgr->StopTCPCServer();
        }
    }

    void TCPClientSendMessage(NetManager *Mgr, const char *Msg, int Len)
    {
        if(Mgr != nullptr)
        {
            Mgr->TCPClientSendMessage(Msg, Len);
        }
    }

}
