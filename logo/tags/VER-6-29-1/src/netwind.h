// -*- c++ -*-
// Copyright (C) 1995 by the Regents of the University of California
// Copyright (C) 1995 by George Mills
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef __NETWND_H_
#define __NETWND_H_

#include <windows.h>
#include <winsock.h>

struct NODE;

// Abstract base class for network connections
class CNetworkConnection 
{
public:
    CNetworkConnection();

    void
    Enable(
        const char *    OnSendReady,
        const char *    OnReceiveReady,
        unsigned int    ServerPort,
        const char *    HostName,
        DWORD           ResolvedHostNameMessage
        );

    bool IsEnabled() const;
    void Disable();

    NODE * GetLastPacketReceived() const;
    void SetLastPacketReceived(char * LastPacket);

    void Shutdown();

    bool
    SendValue(
        const char * Data
        );

protected:
    ~CNetworkConnection() {} // enforce abstract class

    // private helper functions
    void
    AsyncReceive(
        HWND                 WindowHandle,
        const char *         ErrorMessage
        );

    void
    AsyncClose(
        HWND                 WindowHandle
        );

    void
    PostOnSendReadyEvent(
        HWND                 WindowHandle
        );

    // private member variables
    SOCKET       m_Socket;     // socket for the connection
    unsigned int m_Port;       // server's listen port

    bool         m_IsConnected;  // socket is connected
    bool         m_IsBusy;       // socket is too busy to send
    bool         m_IsEnabled;    // if message processing is enabled for this socket

    union _union_host_entry_buffer
    {
        HOSTENT  Entry;                    // The host entry
        char     Buffer[MAXGETHOSTSTRUCT]; // enough space for host entry
    } m_HostEntry;

    char * m_OnReceiveReady;  // Buffer for receive callback
    char * m_OnSendReady;     // Buffer for send    callback
    char * m_ReceiveValue;    // pointer to the last packet received


    // Private helper class for buffering (carrying over) network
    // data from  one "receive" call to another.
    class CCarryOverBuffer 
    {
    public:
        CCarryOverBuffer();

        void ReleaseBuffer();

        void Append(const char * AppendBuffer, int AppendBufferLength);
        void ShiftLeft(int ShiftAmount);

        char * m_Buffer;
        int    m_BufferSize;
        int    m_BytesOfData;
    };

    CCarryOverBuffer m_CarryOverData;  // a buffer for carrying over partial packets 
                                       // from one recv() call to the next.
};

// Class for client network connections
class CClientNetworkConnection : public CNetworkConnection
{
public:
    int
    OnConnectSendAck(
        HWND        WindowHandle,
        LONG        LParam
        );

    int
    OnConnectSendFinish(
        HWND        WindowHandle,
        LONG        LParam
        );
};


// Class for server network connections
class CServerNetworkConnection : public CNetworkConnection
{
public:
    int
    OnListenReceiveAck(
        HWND        WindowHandle,
        LONG        LParam
        );

    int
    OnListenReceiveFinish(
        HWND        WindowHandle,
        LONG        LParam
        );
};

// function declarations
extern NODE *lnetaccepton(NODE *args);
extern NODE *lnetacceptoff(NODE *arg);
extern NODE *lnetacceptsendvalue(NODE *args);
extern NODE *lnetacceptreceivevalue(NODE *arg);
extern NODE *lnetconnecton(NODE *args);
extern NODE *lnetconnectoff(NODE *arg);
extern NODE *lnetconnectsendvalue(NODE *args);
extern NODE *lnetconnectreceivevalue(NODE *arg);
extern NODE *lnetstartup(NODE *args);
extern NODE *lnetshutdown(NODE *arg);

// global variables
extern CClientNetworkConnection g_ClientConnection;
extern CServerNetworkConnection g_ServerConnection;

#endif // __NETWND_H_
