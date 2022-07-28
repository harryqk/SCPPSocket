//
// Created by harryqk on 7/21/22.
//

#ifndef SCPPSOCKET_NETMANAGERWORKER_H
#define SCPPSOCKET_NETMANAGERWORKER_H
#include "Connection.h"
namespace scppsocket
{
    class NetManagerWorker
    {
    protected:
        bool IsWorking;
    public:
        bool GetIsWorking() const;

        void SetIsWorking(bool isWorking);

    public:;
        NetManagerWorker();
        virtual ~NetManagerWorker();
        virtual void DoWork() = 0;
        virtual void SendMessage(const char *Msg, int Len) = 0;
        virtual void StopWork() = 0;
        //virtual void BroadcastMessage(const char *Msg, int Len) = 0;

    };
}


#endif //SCPPSOCKET_NETMANAGERWORKER_H
