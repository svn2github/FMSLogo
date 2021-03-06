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

#include "dynamicbuffer.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

const int DEFAULT_BUFFER_SIZE = 256;

#ifdef NDEBUG
#  define ASSERT_COMBOBUFF_INVARIANT
#else
#  define ASSERT_COMBOBUFF_INVARIANT CBufferInvariant invariant(*this)

class CBufferInvariant
{
public:
    CBufferInvariant(const CDynamicBuffer & DynamicBuffer)
        : m_DynamicBuffer(DynamicBuffer)
    {
        AssertInvariant();
    }

    ~CBufferInvariant()
    {
        AssertInvariant();
    }

    void AssertInvariant() const
    {
        if (m_DynamicBuffer.m_Buffer == NULL)
        {
            assert(m_DynamicBuffer.m_BufferStart == 0);
            assert(m_DynamicBuffer.m_BufferLimit == 0);
            assert(m_DynamicBuffer.m_BufferSize  == 0);
        }
        else
        {
            assert(m_DynamicBuffer.m_BufferLimit <= m_DynamicBuffer.m_BufferSize);
            assert(m_DynamicBuffer.m_BufferStart <= m_DynamicBuffer.m_BufferLimit);
            assert(m_DynamicBuffer.m_Buffer[m_DynamicBuffer.m_BufferLimit] == '\0');
        }
    }

private:
    const CDynamicBuffer & m_DynamicBuffer;
};

#endif // NDEBUG

// constructs an empty buffer
CDynamicBuffer::CDynamicBuffer() : 
    m_Buffer(NULL),
    m_BufferSize(0),
    m_BufferStart(0),
    m_BufferLimit(0)
{
    ASSERT_COMBOBUFF_INVARIANT;
}

// deletes the contents of the internal buffer
void CDynamicBuffer::Dispose()
{
    ASSERT_COMBOBUFF_INVARIANT;

    free(m_Buffer);
   
    m_Buffer       = NULL;
    m_BufferSize   = 0;
    m_BufferStart  = 0;
    m_BufferLimit  = 0;
}


// empties the contents of the enternal buffer, but doesn't free it.
void CDynamicBuffer::Empty()
{
    ASSERT_COMBOBUFF_INVARIANT;

    if (m_Buffer != NULL)
    {
        m_Buffer[0]   = '\0';
        m_BufferStart = 0;
        m_BufferLimit = 0;
    }
}

// returns if the buffer contains no data
bool CDynamicBuffer::IsEmpty() const
{
    ASSERT_COMBOBUFF_INVARIANT;

    if (m_Buffer == NULL)
    {
        return true;
    }
    else
    {
        return m_BufferLimit == m_BufferStart;
    }
}

// resizes the buffer to hold a minimum of MinimumLength bytes.
void 
CDynamicBuffer::GrowTo(
    size_t  MinimumLength
    )
{
    ASSERT_COMBOBUFF_INVARIANT;

    // if combo_buff has never been allocated, do so now.
    if (m_Buffer == NULL)
    {
        m_Buffer     = (char *) calloc(DEFAULT_BUFFER_SIZE, sizeof(char));
        m_BufferSize = DEFAULT_BUFFER_SIZE;
    }

    // if it won't fit, then make the buffer bigger
    size_t requiredLength = MinimumLength + 1;
    if (m_BufferSize < requiredLength)
    {
        // Double the size of the buffer, instead of only requesting 
        // requiredLength bytes.  If we don't do this, then printing 
        // a long string takes a *very* long time because we repeatedly
        // reallocate the buffer to be one byte larger.
        size_t newsize = max(m_BufferSize * 2, requiredLength);

        m_Buffer     = (char *) realloc(m_Buffer, newsize);
        m_BufferSize = newsize;
    }
}

// resizes the buffer to hold ExtraLength more bytes.
void
CDynamicBuffer::GrowBy(
    size_t  ExtraLength
    )
{
    ASSERT_COMBOBUFF_INVARIANT;

    // if combo_buff has never been allocated, do so now.
    if (m_Buffer == NULL)
    {
        m_Buffer     = (char *) calloc(DEFAULT_BUFFER_SIZE, sizeof(char));
        m_BufferSize = DEFAULT_BUFFER_SIZE;
    }

    // if it won't fit, then make the buffer bigger
    size_t requiredLength = m_BufferLimit + ExtraLength + 1;
    if (m_BufferSize < requiredLength)
    {
        // Double the size of the buffer, instead of only requesting 
        // requiredLength bytes.  If we don't do this, then printing 
        // a long string takes a *very* long time because we repeatedly
        // reallocate the buffer to be one byte larger.
        size_t newsize = max(m_BufferSize * 2, requiredLength);

        m_Buffer     = (char *) realloc(m_Buffer, newsize);
        m_BufferSize = newsize;
    }
}

// Append a NUL-terminated string to the combo buffer
void 
CDynamicBuffer::AppendString(
    const char * ToAppend
    )
{
    ASSERT_COMBOBUFF_INVARIANT;

    // resize combo_buff to be large enough to hold ToAppend
    size_t toAppendLength = strlen(ToAppend);
    GrowBy(toAppendLength);

    // append ToAppend
    strcpy(m_Buffer + m_BufferLimit, ToAppend);
    m_BufferLimit += toAppendLength;
}

void 
CDynamicBuffer::AppendChar(
    char         ToAppend
    )
{
    ASSERT_COMBOBUFF_INVARIANT;

    // resize combo_buff to be large enough to hold ToAppend
    GrowBy(1);

    // append ToAppend
    m_Buffer[m_BufferLimit    ] =  ToAppend;
    m_Buffer[m_BufferLimit + 1] =  '\0';
    m_BufferLimit++;
}

char *
CDynamicBuffer::GetBuffer(
    void
    )
{
    ASSERT_COMBOBUFF_INVARIANT;
    return m_Buffer + m_BufferStart;
}

size_t
CDynamicBuffer::GetBufferLength(
    void
    ) const
{
    ASSERT_COMBOBUFF_INVARIANT;
    return m_BufferLimit - m_BufferStart;
}

// Returns the next character from the buffer and removes it.
// Returns '\0' if the buffer is empty.
int
CDynamicBuffer::PopChar(
    void
    )
{
    ASSERT_COMBOBUFF_INVARIANT;

    int ch;

    if (IsEmpty())
    {
        ch = '\0';
    }
    else
    {
        ch = m_Buffer[m_BufferStart];
        m_BufferStart++;

        // Check if we can shift the buffer indices to 
        // the beginning of the buffer.  Otherwise, we
        // might keep growing the buffer, instead of using
        // the open part near the beginning.
        if (IsEmpty())
        {
            Empty();
        }
    }

    return ch;
}
