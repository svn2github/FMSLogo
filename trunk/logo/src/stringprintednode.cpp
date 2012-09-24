// Copyright (C) 2012 by David Costanzo
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

#include "stringprintednode.h"

#include "logocore.h"
#include "print.h"
#include "debugheap.h"

CStringPrintedNode::CStringPrintedNode(const NODE * Node) :
    m_DynamicBuffer(NULL)
{
    // First, try to print the node into the fixed-size buffer.
    size_t totalBytesNeeded = PrintNodeToString(
        Node,
        m_FixedBuffer,
        ARRAYSIZE(m_FixedBuffer));

    if (ARRAYSIZE(m_FixedBuffer) < totalBytesNeeded)
    {
        // More space is needed than exists in the fixed-sized buffer.
        m_DynamicBuffer = new char[totalBytesNeeded];
        if (m_DynamicBuffer != NULL)
        {
            // Print the node into the correctly sized buffer.
            size_t newTotalBytesNeeded = PrintNodeToString(
                Node,
                m_DynamicBuffer,
                totalBytesNeeded);

            // The number of bytes needed shouldn't have changed
            // from the first attempt to the second attempt.
            assert(totalBytesNeeded == newTotalBytesNeeded);
        }
    }
}

CStringPrintedNode::~CStringPrintedNode()
{
    delete [] m_DynamicBuffer;
}

const char *
CStringPrintedNode::GetString() const
{
    if (m_DynamicBuffer != NULL)
    {
        return m_DynamicBuffer;
    }
    else
    {
        return m_FixedBuffer;
    }
}
