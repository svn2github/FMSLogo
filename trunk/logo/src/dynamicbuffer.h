// Copyright (C) 2006 by the David Costanzo
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
//

#ifndef _DYNAMICBUFFER_H_
#define _DYNAMICBUFFER_H_

#include <stddef.h>

class CDynamicBuffer 
{
public:
   friend class CBufferInvariant;
   friend void mputcombobox(const char * str);  // HACK
   friend void putcombochar(char ch);           // HACK

   CDynamicBuffer();

   void Empty();
   void Dispose();
   void AppendString(const char * ToAppend);
   void AppendChar(char ToAppend);

private:
   void GrowBy(size_t ExtraLength);

   char * m_Buffer;        // the contents of the dynamic buffer
   size_t m_BufferSize;    // size of the buffer
   size_t m_BufferLength;  // bytes of string in buffer (not including NUL)
};

#endif // _DYNAMICBUFFER_H_
