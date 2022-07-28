#ifndef SCPPSOCKET_LIBRARY_H
#define SCPPSOCKET_LIBRARY_H
void hello();

int Accept();

void StartClient(const char* Address, int Port);

void StartServer(int Port, int MaxConnection);

void StopClient();

void StopServer();

#endif //SCPPSOCKET_LIBRARY_H
