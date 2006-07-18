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

#include "allwind.h"

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
         return "Name too long";
         
      case WSANOTINITIALISED:
         return "Not initialized";

      case WSASYSNOTREADY:
         return "System not ready";

      case WSAVERNOTSUPPORTED:
         return "Version is not supported";

      case WSAESHUTDOWN:
         return "Can't send after socket shutdown";

      case WSAEINTR:
         return "Interrupted system call";

      case WSAHOST_NOT_FOUND:
         return "Authoritative Answer: Host not found";

      case WSATRY_AGAIN:
         return "Non-Authoritative: Host not found, See NETSTARTUP";

      case WSANO_RECOVERY:
         return "Non-recoverable error";

      case WSANO_DATA:
         return "No data record available";

      case WSAEBADF:
         return "Bad file number";
           
      case WSAEWOULDBLOCK:
         return "Operation would block";

      case WSAEINPROGRESS:
         return "Operation now in progress";

      case WSAEALREADY:
         return "Operation already in progress";

      case WSAEFAULT:
         return "Bad address";

      case WSAEDESTADDRREQ:
         return "Destination address required";

      case WSAEMSGSIZE:
         return "Message too long";

      case WSAEPFNOSUPPORT:
         return "Protocol family not supported";
           
      case WSAENOTEMPTY:
         return "Directory not empty";

      case WSAEPROCLIM:
         return "EPROCLIM returned";

      case WSAEUSERS:
         return "EUSERS returned";

      case WSAEDQUOT:
         return "Disk quota exceeded";

      case WSAESTALE:
         return "ESTALE returned";

      case WSAEINVAL:
         return "Invalid argument";

      case WSAEMFILE:
         return "Too many open files";

      case WSAEACCES:
         return "Access denied";
         
      case WSAELOOP:
         return "Too many levels of symbolic links";

      case WSAEREMOTE:
         return "The object is remote";

      case WSAENOTSOCK:
         return "Socket operation on non-socket";

      case WSAEADDRNOTAVAIL:
         return "Can't assign requested address";

      case WSAEADDRINUSE:
         return "Address already in use";

      case WSAEAFNOSUPPORT:
         return "Address family not supported by protocol family";

      case WSAESOCKTNOSUPPORT:
         return "Socket type not supported";
         
      case WSAEPROTONOSUPPORT:
         return "Protocol not supported";

      case WSAENOBUFS:
         return "No buffer space is supported";

      case WSAETIMEDOUT:
         return "Connection timed out";

      case WSAEISCONN:
         return "Socket is already connected";

      case WSAENOTCONN:
         return "Socket is not connected";

      case WSAENOPROTOOPT:
         return "Bad protocol option";

      case WSAECONNRESET:
         return "Connection reset by peer";

      case WSAECONNABORTED:
         return "Software caused connection abort";

      case WSAENETDOWN:
         return "Network is down";

      case WSAENETRESET:
         return "Network was reset";

      case WSAECONNREFUSED:
         return "Connection refused";

      case WSAEHOSTDOWN:
         return "Host is down";
         
      case WSAEHOSTUNREACH:
         return "Host is unreachable";
          
      case WSAEPROTOTYPE:
         return "Protocol is wrong type for socket";
         
      case WSAEOPNOTSUPP:
         return "Operation not supported on socket";

      case WSAENETUNREACH:
         return "ICMP network unreachable";

      case WSAETOOMANYREFS:
          return "Too many references";

      default:
         {
         static char Buffer[32];
         sprintf(Buffer, "Unknown %d", error);
         return Buffer;
         }
      }
   }

// startup network

NODE *lnetstartup(NODE *args)
   {
   // check if already started
   if (network_is_started)
      {
      ShowMessageAndStop("Network Error", "Already Started");
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
   g_ServerConnection.Disable();

   safe_free(g_ServerConnection.m_OnReceiveReady);
   safe_free(g_ServerConnection.m_OnSendReady);
   safe_free(g_ServerConnection.m_ReceiveValue);
   g_ServerConnection.m_CarryOverData.ReleaseBuffer();

   // cleanup send
   g_ClientConnection.Disable();
   safe_free(g_ClientConnection.m_OnReceiveReady);
   safe_free(g_ClientConnection.m_OnSendReady);
   safe_free(g_ClientConnection.m_ReceiveValue);
   g_ClientConnection.m_CarryOverData.ReleaseBuffer();

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

NODE *lnetreceiveon(NODE *args)
   {
   // check sanity
   if (!network_is_started)
      {
      ShowMessageAndStop("Network Error", "Not Started");
      return Unbound;
      }

   if (g_ServerConnection.IsEnabled())
      {
      ShowMessageAndStop("Network Receive Error", "Already On");
      return Falsex;
      }

   // allocate buffers
   if (g_ServerConnection.m_OnReceiveReady == NULL)
      {
      g_ServerConnection.m_OnReceiveReady = (char *) malloc(MAX_BUFFER_SIZE);
      }

   if (g_ServerConnection.m_OnSendReady == NULL)
      {
      g_ServerConnection.m_OnSendReady = (char *) malloc(MAX_BUFFER_SIZE);
      }

   // get args (socket and callback)
   int port = getint(pos_int_arg(args));

   char networksend[MAX_BUFFER_SIZE];
   cnv_strnode_string(networksend, cdr(args));

   char networkreceive[MAX_BUFFER_SIZE];
   cnv_strnode_string(networkreceive, cdr(cdr(args)));

   if (NOT_THROWING)
      {
      // copy callback (I really should keep these as true Nodes)
      strcpy(g_ServerConnection.m_OnReceiveReady, networkreceive);
      strcpy(g_ServerConnection.m_OnSendReady, networksend);

      // save socket globally
      g_ServerConnection.m_Port = port;

      // open the socket

#ifdef USE_UDP
      if ((g_ServerConnection.m_Socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
#else
      if ((g_ServerConnection.m_Socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
#endif
         {
         ShowMessageAndStop("socket(receivesock)", WSAGetLastErrorString(0));
         return Falsex;
         }

      // get who we are
      char szThisHost[80];
      gethostname(szThisHost, sizeof(szThisHost));

      if (network_dns_sync == 1)
         {
         g_ServerConnection.m_HostEntry = gethostbyname(szThisHost);
         if (g_ServerConnection.m_HostEntry != NULL)
            {
            ShowMessageAndStop("gethostbyname(thishost)", WSAGetLastErrorString(0));
            return Falsex;
            }

         g_ServerConnection.m_IsEnabled = true;
         MainWindowx->SendMessage(WM_NETWORK_LISTENRECEIVEFINISH, 0, 0);
         }
      else
         {
         if (g_ServerConnection.m_HostEntry == NULL)
            {
            g_ServerConnection.m_HostEntry = (PHOSTENT) calloc(1, MAXGETHOSTSTRUCT);
            }

         HANDLE getHostByNameHandle = WSAAsyncGetHostByName(
            MainWindowx->HWindow, 
            WM_NETWORK_LISTENRECEIVEFINISH, 
            szThisHost, 
            (LPSTR) g_ServerConnection.m_HostEntry, 
            MAXGETHOSTSTRUCT);
         if (getHostByNameHandle == NULL)
            {
            ShowMessageAndStop("WSAAsyncGetHostByName()", WSAGetLastErrorString(0));
            return Falsex;
            }

         g_ServerConnection.m_IsEnabled = true;
         // wait for callback
         }

      return Truex;
      }

   return Unbound;
   }

NODE *lnetreceiveoff(NODE *)
   {
   // tell handler not to do anything with messages for network receive
   if (g_ServerConnection.IsEnabled())
      {
      g_ServerConnection.Disable();
      }
   else
      {
      ShowMessageAndStop("Network Receive Error", "Already Off");
      }

   return Unbound;
   }

NODE *lnetreceivereceivevalue(NODE *)
   {
   // return current network value
   if (g_ServerConnection.IsEnabled())
      {
      if (g_ServerConnection.m_ReceiveValue == NULL)
         {
         return NIL;
         }
      else
         {
         NODE* targ = make_strnode(g_ServerConnection.m_ReceiveValue);
         NODE* val = parser(targ, false);
         return val;
         }
      }

   return Unbound;
   }

NODE *lnetsendreceivevalue(NODE *)
   {
   // return current network value
   if (g_ClientConnection.IsEnabled())
      {
      if (g_ClientConnection.m_ReceiveValue == NULL)
         {
         return NIL;
         }
      else
         {
         NODE* targ = make_strnode(g_ClientConnection.m_ReceiveValue);
         NODE* val = parser(targ, false);
         return val;
         }
      }

   return Unbound;
   }

NODE *lnetsendon(NODE *args)
   {
   // sanity check first
   if (!network_is_started)
      {
      ShowMessageAndStop("Network Error", "Not Started");
      return Unbound;
      }

   if (g_ClientConnection.IsEnabled())
      {
      ShowMessageAndStop("Network Send Error", "Already On");
      return Falsex;
      }

   // allocate the callback buffer

   if (g_ClientConnection.m_OnSendReady == NULL)
      {
      g_ClientConnection.m_OnSendReady = (char *) malloc(MAX_BUFFER_SIZE);
      }

   if (g_ClientConnection.m_OnReceiveReady == NULL)
      {
      g_ClientConnection.m_OnReceiveReady = (char *) malloc(MAX_BUFFER_SIZE);
      }

   // get args (remotemachinename, socket, callback)
   char networkaddress[MAX_BUFFER_SIZE];
   cnv_strnode_string(networkaddress, args);

   int remote_port = getint(pos_int_arg(cdr(args)));

   char networksend[MAX_BUFFER_SIZE];
   cnv_strnode_string(networksend, cdr(cdr(args)));

   char networkreceive[MAX_BUFFER_SIZE];
   cnv_strnode_string(networkreceive, cdr(cdr(cdr(args))));

   if (NOT_THROWING)
      {
      // copy the callback
      strcpy(g_ClientConnection.m_OnSendReady, networksend);
      strcpy(g_ClientConnection.m_OnReceiveReady, networkreceive);

      // save the port globally
      g_ClientConnection.m_Port = remote_port;

      // get sockets
#ifdef USE_UDP
      g_ClientConnection.m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
#else
      g_ClientConnection.m_Socket = socket(AF_INET, SOCK_STREAM, 0);
#endif
      if (g_ClientConnection.m_Socket == INVALID_SOCKET)
         {
         ShowMessageAndStop("socket(sendsocket)", WSAGetLastErrorString(0));
         return Falsex;
         }

      if (network_dns_sync == 1)
         {
         g_ClientConnection.m_HostEntry = gethostbyname(networkaddress);
         if (g_ClientConnection.m_HostEntry == NULL)
            {
            ShowMessageAndStop("gethostbyname(host)", WSAGetLastErrorString(0));
            return Falsex;
            }

         g_ClientConnection.m_IsEnabled = true;
         MainWindowx->SendMessage(WM_NETWORK_CONNECTSENDFINISH, 0, 0);
         }
      else
         {
         if (g_ClientConnection.m_HostEntry == NULL)
            {
            g_ClientConnection.m_HostEntry = (PHOSTENT) calloc(1, MAXGETHOSTSTRUCT);
            }

         // get address of remote machine
         HANDLE getHostByNameHandle = WSAAsyncGetHostByName(
            MainWindowx->HWindow, 
            WM_NETWORK_CONNECTSENDFINISH, 
            networkaddress, 
            (LPSTR) g_ClientConnection.m_HostEntry, 
            MAXGETHOSTSTRUCT);
         if (getHostByNameHandle == NULL)
            {
            ShowMessageAndStop("WSAAsyncGetHostByName()", WSAGetLastErrorString(0));
            return Falsex;
            }

         g_ClientConnection.m_IsEnabled = true;
         // wait for callback
         }

      return Truex;
      }

   return Unbound;
   }

NODE *lnetsendoff(NODE *)
   {
   // tell handler not to do anything with messages for network send
   if (g_ClientConnection.IsEnabled())
      {
      g_ClientConnection.Disable();
      }
   else
      {
      ShowMessageAndStop("Network Send Error", "Already Off");
      }

   return Unbound;
   }

NODE *lnetsendsendvalue(NODE *args)
   {
   // get args (data)
   char Data[MAX_BUFFER_SIZE];
   cnv_strnode_string(Data, args);

   if (NOT_THROWING)
      {
      if (g_ClientConnection.m_IsConnected && !g_ClientConnection.m_IsBusy)
         {

         // send the data
         if ((send(g_ClientConnection.m_Socket, Data, strlen(Data) + 1, 0)) == SOCKET_ERROR)
            {

            if (WSAGetLastError() != WSAEWOULDBLOCK)
               {
               ShowMessageAndStop("send(sendsock)", WSAGetLastErrorString(0));
               return Falsex;
               }

            // Idle Until it's ok again.
            g_ClientConnection.m_IsBusy = true;
            return Falsex;
            }
         }
      else
         {
         return Falsex;
         }

      return Truex;
      }

   return Unbound;
   }

NODE *lnetreceivesendvalue(NODE *args)
   {
   // get args (data)
   char Data[MAX_BUFFER_SIZE];
   cnv_strnode_string(Data, args);

   if (NOT_THROWING)
      {
      if (g_ServerConnection.m_IsConnected && !g_ServerConnection.m_IsBusy)
         {
         // send the data
         if ((send(g_ServerConnection.m_Socket, Data, strlen(Data) + 1, 0)) == SOCKET_ERROR)
            {
            if (WSAGetLastError() != WSAEWOULDBLOCK)
               {
               ShowMessageAndStop("send(sendsock)", WSAGetLastErrorString(0));
               return Falsex;
               }

            // Idle Until it's ok again.
            g_ServerConnection.m_IsBusy = true;
            return Falsex;
            }
         }
      else
         {
         return Falsex;
         }

      return Truex;
      }

   return Unbound;
   }

