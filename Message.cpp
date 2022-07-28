//
// Created by harryqk on 7/19/22.
//

#include "Message.h"
namespace scppsocket
{
    Message::Message(char* Data, int Len)
    {
        this->Data = Data;
        this->Len = Len;
    }

    Message::~Message()
    {
        delete Data;
        Data = nullptr;
    }
}