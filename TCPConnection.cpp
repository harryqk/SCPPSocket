//
// Created by harryqk on 7/21/22.
//

#include "TCPConnection.h"

namespace scppsocket
{
    SockSSize_t TCPConnection::Send(const char *buf, SockSize_t Len)
    {
        size_t nleft = 0;
        size_t nwritten = 0;
        char *pwrite_buf = nullptr;
        SSocket Sock = SSock->GetFileDescriptor();
        if ((Sock <= 0) || (nullptr == buf) || (Len < 0))
        {
            return -1;
        }

        pwrite_buf = (char *)buf;
        nleft = Len;

        while(nleft>0)
        {
            if (-1 == (nwritten = SSock->Send(pwrite_buf, nleft, 0)))
            {
                if (EINTR == errno || EWOULDBLOCK == errno || EAGAIN == errno)
                {
                    nwritten = 0;
                }
                else
                {
                    std::printf("%s,%d, Send() -1, 0x%x\n", __FILE__, __LINE__, errno);
                    return -1;
                }
            }
            nleft -= nwritten;
            pwrite_buf += nwritten;
        }

        return(Len);
    }

    void TCPConnection::PushSendMessage(char *buf, SockSize_t Len)
    {
        Message* Msg = new Message(buf, Len);
        std::lock_guard<std::mutex> guard(MutexSend);
        SendMessage.push(Msg);
        MutexSend.unlock();
    }

    bool TCPConnection::SendAll()
    {
        int result;
        bool ret = true;
        std::lock_guard<std::mutex> guard(MutexSend);
        while (!SendMessage.empty())
        {
            Message* Msg = SendMessage.front();
            SendMessage.pop();
            result = Send(Msg->Data, Msg->Len);
            if(result < 0)
            {
                ret = false;
            }
            delete Msg;
        }
        MutexSend.unlock();
        return ret;
    }

    SockSSize_t TCPConnection::Read(char* buf, SockSize_t Len)
    {
        SockSize_t nleft = 0;
        SockSize_t nread = 0;
        char* pread_buf = buf;
        nleft = Len;
        while (nleft > 0)
        {
            nread = SSock->Read(pread_buf, nleft, 0);
            if (nread < 0)
            {
                if (EINTR == errno || EWOULDBLOCK == errno || EAGAIN == errno)
                {
                    nread = 0;
                }
                else
                {
                    return -1;
                }
            }
            else if (nread == 0)
            {
                break;
            }
            else
            {
                nleft -= nread;
                pread_buf += nread;
            }
        }
        return Len - nleft;
    }

    void TCPConnection::PushReadMessage(char *buf, SockSize_t Len)
    {
        Message* Msg = new Message(buf, Len);
        std::lock_guard<std::mutex> guard(MutexRead);
        ReadMessage.push(Msg);
        MutexRead.unlock();
    }

    Message *TCPConnection::PopReadMessage()
    {
        Message* Msg = nullptr;
        std::lock_guard<std::mutex> guard(MutexRead);
        if(!ReadMessage.empty())
        {
            Msg = ReadMessage.front();
            ReadMessage.pop();
        }
        MutexRead.unlock();
        return Msg;
    }

    TCPConnection::TCPConnection(SCPPSocket* sSock): Connection(sSock)
    {
        std::printf("construct TCPConnection\n");
    }

    TCPConnection::~TCPConnection()
    {
        std::printf("destruct TCPConnection\n");
    }
}