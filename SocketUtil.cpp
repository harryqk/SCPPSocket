//
// Created by harryqk on 7/22/22.
//

#include "SocketUtil.h"
#include <iostream>
namespace scppsocket
{

    void SocketUtil::IntToByte(int i, unsigned char *bytes, int size)
    {
        memset(bytes,0,sizeof(byte) *  size);
        bytes[0] = (byte) (0xff & i);
        bytes[1] = (byte) ((0xff00 & i) >> 8);
        bytes[2] = (byte) ((0xff0000 & i) >> 16);
        bytes[3] = (byte) ((0xff000000 & i) >> 24);
    }

    int SocketUtil::BytesToInt(unsigned char *bytes, int size)
    {
        int ret = bytes[0] & 0xFF;
        ret |= ((bytes[1] << 8) & 0xFF00);
        ret |= ((bytes[2] << 16) & 0xFF0000);
        ret |= ((bytes[3] << 24) & 0xFF000000);
        return ret;
    }
}