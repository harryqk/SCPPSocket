//
// Created by harryqk on 7/21/22.
//

#include "NetManagerWorker.h"

namespace scppsocket
{

    bool NetManagerWorker::GetIsWorking() const
    {
        return IsWorking;
    }

    void NetManagerWorker::SetIsWorking(bool isWorking)
    {
        IsWorking = isWorking;
    }

    NetManagerWorker::NetManagerWorker()
    {
        IsWorking = false;
        std::printf("construct NetManagerWorker\n");
    }

    NetManagerWorker::~NetManagerWorker()
    {
        std::printf("destruct NetManagerWorker\n");
    }

}


