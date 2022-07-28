#include "library.h"

#include <iostream>
#include "NetManager.h"

using namespace scppsocket;

void hello() {

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

void StartClient(const char *Address, int Port)
{
    //Mgr.StartTCPClient(Address, Port);
}

void StartServer(int Port, int MaxConnection)
{
    //Mgr.StartTCPServer(Port, MaxConnection);
}

void StopClient()
{
    //Mgr.StopTCPClient();
}

void StopServer()
{
    //Mgr.StopTCPClient();
}
