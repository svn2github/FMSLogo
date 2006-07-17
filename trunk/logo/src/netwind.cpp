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

SOCKET       sendSock    = INVALID_SOCKET;   // Current Handle Send Socket
SOCKET       receiveSock = INVALID_SOCKET;   // Current Handle receive Socket
unsigned int sendPort;                       // Current requested send Port
unsigned int receivePort;                    // Current requested receive Port

bool bSendConnected    = false;        // Flag that send socket is connected
bool bSendBusy         = false;        // Flag that send socket is busy
bool bReceiveConnected = false;        // Flag that receive socket is connected
bool bReceiveBusy      = false;        // Flag that receive socket is busy

PHOSTENT phes = NULL;                  // Pointer to Host Entry for send
PHOSTENT pher = NULL;                  // Pointer to Host Entry for receive

char *network_receive_receive = NULL;  // Buffer for receive callback
char *network_receive_send = NULL;     // Buffer for send callback
char *network_receive_value = NULL;    // Buffer for current received data

char *network_send_receive = NULL;     // Buffer for receive callback
char *network_send_send = NULL;        // Buffer for send callback
char *network_send_value = NULL;       // Buffer for current received data

bool network_send_on    = false;    // flag for send enabled (enables message processing)
bool network_receive_on = false;    // flag for receive enabled (enabled message processing)

CCarryOverBuffer g_SendCarryOverData;
CCarryOverBuffer g_ReceiveCarryOverData;

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
   if (network_receive_on)
      {
      network_receive_on = false;
      bReceiveConnected  = false;
      bReceiveBusy       = false;

      closesocket(receiveSock);
      receiveSock = INVALID_SOCKET;
      }
   safe_free(network_receive_receive);
   safe_free(network_receive_send);
   safe_free(network_receive_value);
   g_ReceiveCarryOverData.ReleaseBuffer();

   // cleanup send
   if (network_send_on)
      {
      network_send_on = false;
      bSendConnected  = false;
      bSendBusy       = false;

      closesocket(sendSock);
      sendSock = INVALID_SOCKET;
      }
   safe_free(network_send_receive);
   safe_free(network_send_send);
   safe_free(network_send_value);
   g_SendCarryOverData.ReleaseBuffer();

   // cleanup library
   if (network_is_started) 
      {
      WSACleanup();
      network_is_started = false;
      }

   if (network_dns_sync != 1)
      {
      free(phes);
      free(pher);
      }
   phes = NULL;
   pher = NULL;

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

   if (network_receive_on)
      {
      ShowMessageAndStop("Network Receive Error", "Already On");
      return Falsex;
      }

   // allocate buffers
   if (network_receive_receive == NULL)
      {
      network_receive_receive = (char *) malloc(MAX_BUFFER_SIZE);
      }

   if (network_receive_send == NULL)
      {
      network_receive_send = (char *) malloc(MAX_BUFFER_SIZE);
      }

   // get args (socket and callback)
   int isocket = getint(pos_int_arg(args));

   char networksend[MAX_BUFFER_SIZE];
   cnv_strnode_string(networksend, cdr(args));

   char networkreceive[MAX_BUFFER_SIZE];
   cnv_strnode_string(networkreceive, cdr(cdr(args)));

   if (NOT_THROWING)
      {
      // copy callback (I really should keep these as true Nodes)
      strcpy(network_receive_receive, networkreceive);
      strcpy(network_receive_send, networksend);

      // save socket globally
      receivePort = isocket;

      // open the socket

#ifdef USE_UDP
      if ((receiveSock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
#else
      if ((receiveSock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
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
         pher = gethostbyname(szThisHost);
         if (pher != NULL)
            {
            ShowMessageAndStop("gethostbyname(thishost)", WSAGetLastErrorString(0));
            return Falsex;
            }

         network_receive_on = true;
         MainWindowx->SendMessage(WM_NETWORK_LISTENRECEIVEFINISH, 0, 0);
         }
      else
         {
         if (pher == NULL)
            {
            pher = (PHOSTENT) calloc(1, MAXGETHOSTSTRUCT);
            }

         HANDLE getHostByNameHandle = WSAAsyncGetHostByName(
            MainWindowx->HWindow, 
            WM_NETWORK_LISTENRECEIVEFINISH, 
            szThisHost, 
            (LPSTR) pher, 
            MAXGETHOSTSTRUCT);
         if (getHostByNameHandle == NULL)
            {
            ShowMessageAndStop("WSAAsyncGetHostByName()", WSAGetLastErrorString(0));
            return Falsex;
            }

         network_receive_on = true;
         // wait for callback
         }

      return Truex;
      }

   return Unbound;
   }

NODE *lnetreceiveoff(NODE *)
   {
   // tell handler not to do anything with messages for network receive
   if (network_receive_on)
      {
      network_receive_on = false;
      bReceiveConnected  = false;
      bReceiveBusy       = false;

      safe_free(network_receive_value);

      closesocket(receiveSock);
      receiveSock = INVALID_SOCKET;
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
   if (network_receive_on)
      {
      if (network_receive_value == NULL)
         {
         return NIL;
         }
      else
         {
         NODE* targ = make_strnode(network_receive_value);
         NODE* val = parser(targ, false);
         return val;
         }
      }

   return Unbound;
   }

NODE *lnetsendreceivevalue(NODE *)
   {
   // return current network value
   if (network_send_on)
      {
      if (network_send_value == NULL)
         {
         return NIL;
         }
      else
         {
         NODE* targ = make_strnode(network_send_value);
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

   if (network_send_on)
      {
      ShowMessageAndStop("Network Send Error", "Already On");
      return Falsex;
      }

   // allocate the callback buffer

   if (network_send_send == NULL)
      {
      network_send_send = (char *) malloc(MAX_BUFFER_SIZE);
      }

   if (network_send_receive == NULL)
      {
      network_send_receive = (char *) malloc(MAX_BUFFER_SIZE);
      }

   // get args (remotemachinename, socket, callback)
   char networkaddress[MAX_BUFFER_SIZE];
   cnv_strnode_string(networkaddress, args);

   int isocket = getint(pos_int_arg(cdr(args)));

   char networksend[MAX_BUFFER_SIZE];
   cnv_strnode_string(networksend, cdr(cdr(args)));

   char networkreceive[MAX_BUFFER_SIZE];
   cnv_strnode_string(networkreceive, cdr(cdr(cdr(args))));

   if (NOT_THROWING)
      {
      // copy the callback
      strcpy(network_send_send, networksend);
      strcpy(network_send_receive, networkreceive);

      // save the socket globally
      sendPort = isocket;

      // get sockets
#ifdef USE_UDP
      sendSock = socket(AF_INET, SOCK_DGRAM, 0);
#else
      sendSock = socket(AF_INET, SOCK_STREAM, 0);
#endif
      if (sendSock == INVALID_SOCKET)
         {
         ShowMessageAndStop("socket(sendsocket)", WSAGetLastErrorString(0));
         return Falsex;
         }

      if (network_dns_sync == 1)
         {
         phes = gethostbyname(networkaddress);
         if (phes == NULL)
            {
            ShowMessageAndStop("gethostbyname(host)", WSAGetLastErrorString(0));
            return Falsex;
            }

         network_send_on = true;
         MainWindowx->SendMessage(WM_NETWORK_CONNECTSENDFINISH, 0, 0);
         }
      else
         {
         if (phes == NULL)
            {
            phes = (PHOSTENT) calloc(1, MAXGETHOSTSTRUCT);
            }

         // get address of remote machine
         HANDLE getHostByNameHandle = WSAAsyncGetHostByName(
            MainWindowx->HWindow, 
            WM_NETWORK_CONNECTSENDFINISH, 
            networkaddress, 
            (LPSTR) phes, 
            MAXGETHOSTSTRUCT);
         if (getHostByNameHandle == NULL)
            {
            ShowMessageAndStop("WSAAsyncGetHostByName()", WSAGetLastErrorString(0));
            return Falsex;
            }

         network_send_on = true;
         // wait for callback
         }

      return Truex;
      }

   return Unbound;
   }

NODE *lnetsendoff(NODE *)
   {
   // tell handler not to do anything with messages for network send
   if (network_send_on)
      {
      network_send_on = false;
      bSendConnected  = false;
      bSendBusy       = false;

      safe_free(network_send_value);

      closesocket(sendSock);
      sendSock = INVALID_SOCKET;
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
      if (bSendConnected && !bSendBusy)
         {

         // send the data
         if ((send(sendSock, Data, strlen(Data) + 1, 0)) == SOCKET_ERROR)
            {

            if (WSAGetLastError() != WSAEWOULDBLOCK)
               {
               ShowMessageAndStop("send(sendsock)", WSAGetLastErrorString(0));
               return Falsex;
               }

            // Idle Until it's ok again.
            bSendBusy = true;
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
      if (bReceiveConnected && !bReceiveBusy)
         {
         // send the data
         if ((send(receiveSock, Data, strlen(Data) + 1, 0)) == SOCKET_ERROR)
            {
            if (WSAGetLastError() != WSAEWOULDBLOCK)
               {
               ShowMessageAndStop("send(sendsock)", WSAGetLastErrorString(0));
               return Falsex;
               }

            // Idle Until it's ok again.
            bReceiveBusy = true;
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

