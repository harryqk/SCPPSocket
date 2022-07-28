//
// Created by harryqk on 7/17/22.
//

#include "SCPPSocket.h"

namespace scppsocket
{

    SCPPSocket::SCPPSocket()
    {
        BlockMode = SocketBlockMode::Block;
    }

    void SCPPSocket::SetConnectionState(SocketConnectionState connectionState)
    {
        ConnectionState = connectionState;
    }

    SocketBlockMode SCPPSocket::GetBlockMode() const
    {
        return BlockMode;
    }

    SSocket SCPPSocket::GetFileDescriptor() const
    {
        return FileDescriptor;
    }

    void SCPPSocket::SetFileDescriptor(SSocket fileDescriptor)
    {
        FileDescriptor = fileDescriptor;
    }

    const sockaddr_in &SCPPSocket::GetLocalAddress() const
    {
        return LocalAddress;
    }

    void SCPPSocket::SetLocalAddress(const sockaddr_in &localAddress)
    {
        LocalAddress = localAddress;
    }

    const sockaddr_in &SCPPSocket::GetPeerAddress() const
    {
        return PeerAddress;
    }

    void SCPPSocket::SetPeerAddress(const sockaddr_in &peerAddress)
    {
        PeerAddress = peerAddress;
    }

    SCPPSocket::SCPPSocket(SocketAddressFamily AddressFamily, SocketType Type, SocketProtocol Protocol)
    {
        BlockMode = SocketBlockMode::Block;
    }

    SCPPSocket::~SCPPSocket()
    {

    }

    SocketConnectionState SCPPSocket::GetConnectionState()
    {
        return ConnectionState;
    }


}