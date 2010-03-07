/*
 *
 *       Copyright (C) 1995 by the Regents of the University of California
 *       Copyright (C) 1995 by George Mills
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include "netwind.h"
#include "mainwind.h"

#include "init.h"
#include "main.h"
#include "logodata.h"
#include "logorc.h"
#include "lists.h"
#include "eval.h"
#include "logomath.h"
#include "parse.h"
#include "localizedstrings.h"

CNetworkConnection g_ClientConnection;
CNetworkConnection g_ServerConnection;

static int network_dns_sync = 0;

static bool network_is_started = false;

void
safe_free(
    char * & buffer
    )
{
    free(buffer);
    buffer = NULL;
}

CCarryOverBuffer::CCarryOverBuffer() :
    m_Buffer(NULL),
    m_BufferSize(0),
    m_BytesOfData(0)
{
}

void
CCarryOverBuffer::ReleaseBuffer()
{
    safe_free(m_Buffer);

    m_BytesOfData = 0;
    m_BufferSize  = 0;
}

void
CCarryOverBuffer::Append(
    const char * AppendBuffer,
    int          AppendBufferLength
    )
{
    if (m_BufferSize < m_BytesOfData + AppendBufferLength + 1)
    {
        // there isn't enough room on the buffer.  Grow it.

        m_BufferSize += AppendBufferLength + 1; // leave room for NUL

        m_Buffer = (char*) realloc(m_Buffer, m_BufferSize);
    }

    memcpy(m_Buffer + m_BytesOfData, AppendBuffer, AppendBufferLength);

    m_BytesOfData += AppendBufferLength;

    // always keep m_Buffer NUL-terminated
    m_Buffer[m_BytesOfData] = '\0';
}

void
CCarryOverBuffer::ShiftLeft(
    int ShiftAmount
    )
{
    assert(0 <= ShiftAmount);
    assert(ShiftAmount <= m_BytesOfData);

    // shift the buffer such that it begins at "begin"
    memmove(m_Buffer, m_Buffer + ShiftAmount, m_BytesOfData - ShiftAmount);
   
    m_BytesOfData -= ShiftAmount;
}


CNetworkConnection::CNetworkConnection() :
    m_Socket(INVALID_SOCKET),
    m_Port(0),
    m_IsConnected(false),
    m_IsBusy(false),
    m_IsEnabled(false),
    m_HostEntry(NULL),
    m_OnReceiveReady(NULL),
    m_OnSendReady(NULL),
    m_ReceiveValue(NULL)
{
}

void
CNetworkConnection::SetLastPacketReceived(
    char * LastPacket
    )
{
    free(m_ReceiveValue);
    m_ReceiveValue = LastPacket;
}

NODE*
CNetworkConnection::GetLastPacketReceived() const
{
    if (m_ReceiveValue == NULL)
    {
        return NIL;
    }
    else
    {
        NODE* targ = make_strnode(m_ReceiveValue);
        NODE* val = parser(targ, false);
        return val;
    }
}

bool
CNetworkConnection::IsEnabled() const
{
    return m_IsEnabled;
}

void
CNetworkConnection::Disable()
{
    if (IsEnabled())
    {
        m_IsEnabled    = false;
        m_IsConnected  = false;
        m_IsBusy       = false;

        safe_free(m_ReceiveValue);

        closesocket(m_Socket);
        m_Socket = INVALID_SOCKET;
    }
}

void
CNetworkConnection::Enable(
    const char *    OnSendReady,
    const char *    OnReceiveReady,
    unsigned int    ServerPort,
    const char *    HostName,
    DWORD           ResolvedHostNameMessage
    )
{

    // copy the receive ready callback
    if (m_OnReceiveReady == NULL)
    {
        m_OnReceiveReady = (char *) malloc(MAX_BUFFER_SIZE);
    }
    strcpy(m_OnReceiveReady, OnReceiveReady);

    // copy the send ready callback
    if (m_OnSendReady == NULL)
    {
        m_OnSendReady = (char *) malloc(MAX_BUFFER_SIZE);
    }
    strcpy(m_OnSendReady, OnSendReady);

    // copy the server port
    m_Port = ServerPort;

    // get sockets
#ifdef USE_UDP
    m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
#else
    m_Socket = socket(AF_INET, SOCK_STREAM, 0);
#endif

    if (m_Socket == INVALID_SOCKET)
    {
        ShowMessageAndStop("socket()", WSAGetLastErrorString(0));
        return;
    }

    if (network_dns_sync == 1)
    {
        m_HostEntry = gethostbyname(HostName);
        if (m_HostEntry == NULL)
        {
            ShowMessageAndStop("gethostbyname(host)", WSAGetLastErrorString(0));
            return;
        }

        m_IsEnabled = true;
        MainWindowx->SendMessage(ResolvedHostNameMessage, 0, 0);
    }
    else
    {
        if (m_HostEntry == NULL)
        {
            m_HostEntry = (PHOSTENT) calloc(1, MAXGETHOSTSTRUCT);
        }

        // get address of remote machine
        HANDLE getHostByNameHandle = WSAAsyncGetHostByName(
            MainWindowx->HWindow, 
            ResolvedHostNameMessage, 
            HostName, 
            (LPSTR) m_HostEntry, 
            MAXGETHOSTSTRUCT);
        if (getHostByNameHandle == NULL)
        {
            ShowMessageAndStop("WSAAsyncGetHostByName()", WSAGetLastErrorString(0));
            return;
        }

        m_IsEnabled = true;
        // wait for callback
    }
}

bool
CNetworkConnection::SendValue(
    const char * Data
    )
{
    if (m_IsConnected && !m_IsBusy)
    {
        // send the data
        int rval = send(m_Socket, Data, strlen(Data) + 1, 0);
        if (rval == SOCKET_ERROR)
        {
            if (WSAGetLastError() != WSAEWOULDBLOCK)
            {
                ShowMessageAndStop("send(socket)", WSAGetLastErrorString(0));
                return false;
            }

            // Don't send anymore until we receive confirmation
            // that the remote side received the data.
            m_IsBusy = true;
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

void
CNetworkConnection::AsyncReceive(
    TWindow    *         Window,
    const char *         ErrorMessage
    )
{
    char buffer[MAX_PACKET_SIZE];
    memset(buffer, 0, MAX_PACKET_SIZE);

    // read the data from the buffer
    int status = recv(m_Socket, buffer, sizeof(buffer) - 1, 0);
    if (status == SOCKET_ERROR)
    {
        // if this would block, we just wait until we get called again
        if (WSAGetLastError() != WSAEWOULDBLOCK) 
        {
            Window->MessageBox(WSAGetLastErrorString(0), ErrorMessage);
            // err_logo(STOP_ERROR,NIL);
        }
    }
    else
    {
        // we received some data.

        // We have some data left from the last time we were called.
        // Append this buffer to the end of the network receive buffer. 

        // TODO: Don't Append the data to the carry-over buffer if there is none.
        //       We should be able to use buffer, instead.
        m_CarryOverData.Append(buffer, status);

        // now queue up a separate message for each packet
        int begin = 0;
        int end   = strlen(m_CarryOverData.m_Buffer);

        while (end < m_CarryOverData.m_BytesOfData)
        {
            callthing * callevent = callthing::CreateNetworkReceiveReadyEvent(
                this,
                m_CarryOverData.m_Buffer + begin);

            calllists.insert(callevent);
            Window->PostMessage(WM_CHECKQUEUE, 0, 0);

            begin = end + 1;
            end   = begin + strlen(m_CarryOverData.m_Buffer + begin);
        }

        // shift the buffer such that it begins at "begin"
        m_CarryOverData.ShiftLeft(begin);
    }
}

void
CNetworkConnection::AsyncClose(
    TWindow    *         Window
    )
{
    // send any data in the carry-over buffer upwards
    if (m_CarryOverData.m_BytesOfData != 0)
    {
        callthing *callevent = callthing::CreateNetworkReceiveReadyEvent(
            this,
            m_CarryOverData.m_Buffer);
            
        calllists.insert(callevent);
               
        Window->PostMessage(WM_CHECKQUEUE, 0, 0);
    }

    m_CarryOverData.ReleaseBuffer();

    m_IsConnected = false;
}

void
CNetworkConnection::Shutdown()
{
    Disable();

    safe_free(m_OnReceiveReady);
    safe_free(m_OnSendReady);
    SetLastPacketReceived(NULL);
    m_CarryOverData.ReleaseBuffer();
}

void
CNetworkConnection::PostOnSendReadyEvent(
    TWindow  *  Window
    )
{
    // we don't distinguish between all event types
    callthing *callevent = callthing::CreateNoYieldFunctionEvent(m_OnSendReady);

    calllists.insert(callevent);
    Window->PostMessage(WM_CHECKQUEUE, 0, 0);
}


// converts winsock errorcode to string
LPCSTR WSAGetLastErrorString(int error_arg)
{
    int error;

    if (error_arg != 0)
    {
        error = error_arg;
    }
    else
    {
        error = WSAGetLastError();
    }

    switch (error)
    {
    case WSAENAMETOOLONG:
        return LOCALIZED_ERROR_NETWORKNAMETOOLONG;
         
    case WSANOTINITIALISED:
        return LOCALIZED_ERROR_NETWORKNOTINITIALIZED;

    case WSASYSNOTREADY:
        return LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY;

    case WSAVERNOTSUPPORTED:
        return LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED;

    case WSAESHUTDOWN:
        return LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN;

    case WSAEINTR:
        return LOCALIZED_ERROR_NETWORKINTERRUPTED;

    case WSAHOST_NOT_FOUND:
        return LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH;

    case WSATRY_AGAIN:
        return LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH;

    case WSANO_RECOVERY:
        return LOCALIZED_ERROR_NETWORKNOTRECOVERABLE;

    case WSANO_DATA:
        return LOCALIZED_ERROR_NETWORKNODATA;

    case WSAEBADF:
        return LOCALIZED_ERROR_NETWORKBADFILENUMBER;
           
    case WSAEWOULDBLOCK:
        return LOCALIZED_ERROR_NETWORKWOULDBLOCK;

    case WSAEINPROGRESS:
        return LOCALIZED_ERROR_NETWORKNOWINPROGRESS;

    case WSAEALREADY:
        return LOCALIZED_ERROR_NETWORKALREADYINPROGRESS;

    case WSAEFAULT:
        return LOCALIZED_ERROR_NETWORKBADADDRESS;

    case WSAEDESTADDRREQ:
        return LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS;

    case WSAEMSGSIZE:
        return LOCALIZED_ERROR_NETWORKMESSAGETOOLONG;

    case WSAEPFNOSUPPORT:
        return LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED;
           
    case WSAENOTEMPTY:
        return LOCALIZED_ERROR_NETWORKDIRNOTEMPTY;

    case WSAEPROCLIM:
        return LOCALIZED_ERROR_NETWORKAPPLIMITREACHED;

    case WSAEDQUOT:
        return LOCALIZED_ERROR_NETWORKDISKQUOTA;

    case WSAEINVAL:
        return LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS;

    case WSAEMFILE:
        return LOCALIZED_ERROR_NETWORKTOOMANYFILES;

    case WSAEACCES:
        return LOCALIZED_ERROR_NETWORKACCESSDENIED;
         
    case WSAENOTSOCK:
        return LOCALIZED_ERROR_NETWORKNOTASOCKET;

    case WSAEADDRNOTAVAIL:
        return LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE;

    case WSAEADDRINUSE:
        return LOCALIZED_ERROR_NETWORKADDRINUSE;

    case WSAEAFNOSUPPORT:
        return LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED;

    case WSAESOCKTNOSUPPORT:
        return LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED;
         
    case WSAEPROTONOSUPPORT:
        return LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED;

    case WSAENOBUFS:
        return LOCALIZED_ERROR_NETWORKNOBUFFER;

    case WSAETIMEDOUT:
        return LOCALIZED_ERROR_NETWORKTIMEDOUT;

    case WSAEISCONN:
        return LOCALIZED_ERROR_NETWORKALREADYCONNECTED;

    case WSAENOTCONN:
        return LOCALIZED_ERROR_NETWORKNOTCONNECTED;

    case WSAENOPROTOOPT:
        return LOCALIZED_ERROR_NETWORKBADPROTOOPT;

    case WSAECONNRESET:
        return LOCALIZED_ERROR_NETWORKCONNECTIONRESET;

    case WSAECONNABORTED:
        return LOCALIZED_ERROR_NETWORKCONNECTIONABORT;

    case WSAENETDOWN:
        return LOCALIZED_ERROR_NETWORKISDOWN;

    case WSAENETRESET:
        return LOCALIZED_ERROR_NETWORKRESET;

    case WSAECONNREFUSED:
        return LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED;

    case WSAEHOSTDOWN:
        return LOCALIZED_ERROR_NETWORKHOSTISDOWN;
         
    case WSAEHOSTUNREACH:
        return LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE;
          
    case WSAEPROTOTYPE:
        return LOCALIZED_ERROR_NETWORKBADPROTOTYPE;
         
    case WSAEOPNOTSUPP:
        return LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED;

    case WSAENETUNREACH:
        return LOCALIZED_ERROR_NETWORKUNREACHABLE;

    case WSAETOOMANYREFS:
        return LOCALIZED_ERROR_NETWORKTOOMANYREFS;

    default:
        {
            static char buffer[32];
            sprintf(buffer, LOCALIZED_UNKNOWN" %d", error);
            return buffer;
        }
    }
}

// startup network
NODE *lnetstartup(NODE *args)
{
    // check if already started
    if (network_is_started)
    {
        ShowMessageAndStop(
            LOCALIZED_ERROR_NETWORK, 
            LOCALIZED_ERROR_NETWORKALREADYSTARTED);
        return Unbound;
    }

    if (args != NIL)
    {
        network_dns_sync = int_arg(args);
    }

    // tell winsock to wakeup
    WSADATA WSAData;
    if (WSAStartup(MAKEWORD(1,1), &WSAData) != 0)
    {
        ShowMessageAndStop("WSAStartup()", WSAGetLastErrorString(0));
        return Unbound;
    }

    network_is_started = true;
    return Unbound;
}

// put everything back to original state
NODE *lnetshutdown(NODE *)
{
    // cleanup receive
    g_ServerConnection.Shutdown();

    // cleanup send
    g_ClientConnection.Shutdown();

    // cleanup library
    if (network_is_started) 
    {
        WSACleanup();
        network_is_started = false;
    }

    if (network_dns_sync != 1)
    {
        free(g_ClientConnection.m_HostEntry);
        free(g_ServerConnection.m_HostEntry);
    }
    g_ClientConnection.m_HostEntry = NULL;
    g_ServerConnection.m_HostEntry = NULL;

    network_dns_sync = 0;
    return Unbound;
}

// enable receiving
NODE *lnetaccepton(NODE *args)
{
    // check sanity
    if (!network_is_started)
    {
        ShowMessageAndStop(
            LOCALIZED_ERROR_NETWORK, 
            LOCALIZED_ERROR_NETWORKNOTSTARTED);
        return Unbound;
    }

    if (g_ServerConnection.IsEnabled())
    {
        ShowMessageAndStop(
            LOCALIZED_ERROR_NETWORKRECEIVE, 
            LOCALIZED_ERROR_NETWORKALREADYON);
        return Unbound;
    }

    // get args (socket and callback)
    int port = getint(nonnegative_int_arg(args));

    char networksend[MAX_BUFFER_SIZE];
    cnv_strnode_string(networksend, cdr(args));

    char networkreceive[MAX_BUFFER_SIZE];
    cnv_strnode_string(networkreceive, cdr(cdr(args)));

    if (NOT_THROWING)
    {
        // get who we are
        char szThisHost[80];
        gethostname(szThisHost, sizeof(szThisHost));

        g_ServerConnection.Enable(
            networksend,
            networkreceive,
            port,
            szThisHost,
            WM_NETWORK_LISTENRECEIVEFINISH);
    }

    if (NOT_THROWING)
    {
        return Truex.GetNode();
    }

    return Unbound;
}

NODE *lnetacceptoff(NODE *)
{
    // tell handler not to do anything with messages for network receive
    if (g_ServerConnection.IsEnabled())
    {
        g_ServerConnection.Disable();
    }
    else
    {
        ShowMessageAndStop(
            LOCALIZED_ERROR_NETWORKRECEIVE, 
            LOCALIZED_ERROR_NETWORKALREADYOFF);
    }

    return Unbound;
}

NODE *lnetacceptreceivevalue(NODE *)
{
    // return current network value
    if (g_ServerConnection.IsEnabled())
    {
        return g_ServerConnection.GetLastPacketReceived();
    }

    return Unbound;
}

NODE *lnetconnectreceivevalue(NODE *)
{
    // return current network value
    if (g_ClientConnection.IsEnabled())
    {
        return g_ClientConnection.GetLastPacketReceived();
    }

    return Unbound;
}

NODE *lnetconnecton(NODE *args)
{
    // sanity check first
    if (!network_is_started)
    {
        ShowMessageAndStop(
            LOCALIZED_ERROR_NETWORK, 
            LOCALIZED_ERROR_NETWORKNOTSTARTED);
        return Unbound;
    }

    if (g_ClientConnection.IsEnabled())
    {
        ShowMessageAndStop(
            LOCALIZED_ERROR_NETWORKSEND, 
            LOCALIZED_ERROR_NETWORKALREADYON);
        return Unbound;
    }

    // get args (remotemachinename, socket, callback)
    char remotehostname[MAX_BUFFER_SIZE];
    cnv_strnode_string(remotehostname, args);

    int remote_port = getint(nonnegative_int_arg(cdr(args)));

    char networksend[MAX_BUFFER_SIZE];
    cnv_strnode_string(networksend, cdr(cdr(args)));

    char networkreceive[MAX_BUFFER_SIZE];
    cnv_strnode_string(networkreceive, cdr(cdr(cdr(args))));

    if (NOT_THROWING)
    {
        g_ClientConnection.Enable(
            networksend,
            networkreceive,
            remote_port,
            remotehostname,
            WM_NETWORK_CONNECTSENDFINISH);
    }

    if (NOT_THROWING)
    {
        return Truex.GetNode();
    }

    return Unbound;
}

NODE *lnetconnectoff(NODE *)
{
    // tell handler not to do anything with messages for network send
    if (g_ClientConnection.IsEnabled())
    {
        g_ClientConnection.Disable();
    }
    else
    {
        ShowMessageAndStop(
            LOCALIZED_ERROR_NETWORKSEND, 
            LOCALIZED_ERROR_NETWORKALREADYOFF);
    }

    return Unbound;
}

NODE *lnetconnectsendvalue(NODE *args)
{
    // get args (data)
    char data[MAX_BUFFER_SIZE];
    cnv_strnode_string(data, args);

    if (NOT_THROWING)
    {
        // try to send data
        bool isOk = g_ClientConnection.SendValue(data);
        return true_or_false(isOk);
    }

    return Unbound;
}

NODE *lnetacceptsendvalue(NODE *args)
{
    // get args (data)
    char data[MAX_BUFFER_SIZE];
    cnv_strnode_string(data, args);

    if (NOT_THROWING)
    {
        // try to send data
        bool isOk = g_ServerConnection.SendValue(data);
        return true_or_false(isOk);
    }

    return Unbound;
}
