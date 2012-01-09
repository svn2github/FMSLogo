/*
 *  Copyright (C) 1995 by the Regents of the University of California
 *  Copyright (C) 1995 by George Mills
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include "main.h"
#include "utils.h"
#include "ibmterm.h"
#include "logorc.h"
#include "eval.h"
#include "const.h"
#include "wrksp.h"
#include "files.h"
#include "error.h"
#include "init.h"
#include "logodata.h"
#include "activearea.h"
#include "screenwindow.h"
#include "startup.h"

#include "mainwind.h"
#include "netwind.h"
#include "graphwin.h"
#include "statwind.h"
#include "devwind.h"
#include "debugheap.h"

#include "localizedstrings.h"

calllist calllists;

// inserts an element at the front of the list.
void qlist::insert(void * a)
{
    assert(a != NULL && "invalid parameter");

    // class "event list queue" member to insert event
    if (last)
    {
        // list has at least one element.
        qlink * previousHead = last->next;
        qlink * head = new qlink(a, NULL, NULL);
        last->next = head;
        head->prev = last;
        head->next = previousHead;
        previousHead->prev = head;

        last = last->next;
    }
    else
    {
        // list was empty, so this is the new last node
        last = new qlink(a, NULL, NULL);
        last->next = last;
        last->prev = last;
    }
}

// returns the first element in the list.
// returns NULL if the list is empty.
void * qlist::get(void)
{
    if (last == NULL)
    {
        return NULL;
    }

    return last->next->e;
}

// removes the first item in the list
void qlist::zap(void)
{
    if (last == NULL) 
    {
        return;
    }

    qlink * p = last->next;

    if (last == p)
    {
        // this was the only element in the list
        last = NULL;
    }
    else
    {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }

    delete p;
}

// deletes the list structure, but does not modify any of the list elements.
void qlist::clear()
{
    qlink *l = last;

    if (l == NULL) 
    {
        return;
    }

    do
    {
        qlink *ll = l;
        l = l->next;
        delete ll;
    } while (l != last);
}

// removes an element from the list, but does NOT delete the element
void qlist::remove(void * a)
{
    qlink * node = find(a);
    if (node == NULL)
    {
        // the element isn't in the list
        return;
    }

    if (last == node)
    {
        // special case: we are removing the "last" node.
        if (last == last->next)
        {
            // this was the only element in the list
            last = NULL;
        }
        else
        {
            last->next->prev = last->prev;
            last->prev->next = last->next;
            last = node->prev;
        }
    }
    else
    {
        // unlink the node that holds "a" and delete it
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    delete node;
}

// returns an element's node, if it exists
qlink * qlist::find(void * a)
{
    if (last == NULL) 
    {
        // the list is empty
        return NULL;
    }

    // search the list for "a" and remove it.
    qlink * ptr = last;
    do 
    {
        if (ptr->e == a)
        {
            // found it
            return ptr;
        }
        
        ptr = ptr->next;

    } while (ptr != last);
   
    // can't find it
    return NULL;
}

callthing * callthing::CreateKeyboardEvent(char * function, int key)
{
    callthing * callevent = new callthing;
    callevent->kind = EVENTTYPE_Keyboard;
    callevent->func = function;
    callevent->arg1 = key;

    return callevent;
}

callthing * callthing::CreateMouseEvent(char * function, int x, int y)
{
    callthing * callevent = new callthing;
    callevent->kind = EVENTTYPE_Mouse;
    callevent->func = function;
    callevent->arg1 = x;
    callevent->arg2 = y;

    return callevent;
}

callthing * callthing::CreateFunctionEvent(char * function)
{
    callthing * callevent = new callthing;
    callevent->kind = EVENTTYPE_YieldFunction;
    callevent->func = function;

    return callevent;
}

callthing * callthing::CreateNoYieldFunctionEvent(char * function)
{
    callthing * callevent = new callthing;
    callevent->kind = EVENTTYPE_NoYieldFunction;
    callevent->func = function;

    return callevent;
}

callthing * callthing::CreateNetworkReceiveReadyEvent(CNetworkConnection * NetworkConnection, const char * packet)
{
    callthing * callevent = new callthing;
    callevent->kind = EVENTTYPE_NetworkReceiveReady;
   
    callevent->networkconnection = NetworkConnection;

    // copy m_OnReceiveReady now because it might be freed by the time 
    // the event is processed.
    callevent->func = strdup(NetworkConnection->m_OnReceiveReady);

    // copy the network packet into the event (instead of into NetworkConnection) 
    // so that it can be processed in the order in which is was received.
    callevent->networkpacket = strdup(packet);

    return callevent;
}

callthing::~callthing()
{
    switch (kind)
    {
    case EVENTTYPE_NetworkReceiveReady:
        free(func);
        free(networkpacket);
        break;
    }
}

ERR_TYPES WriteDIB(FILE* File, int MaxBitCount)
{
    ERR_TYPES status = SUCCESS;

    // grab a DC 
    HDC screen = CreateDC("DISPLAY", NULL, NULL, NULL);

    // hard code to screen mode
    WORD SavebitCount = GetDeviceCaps(screen, BITSPIXEL);
    SavebitCount *= GetDeviceCaps(screen, PLANES);

    if (MaxBitCount < SavebitCount)
    {
        if ((MaxBitCount == 1) || (MaxBitCount == 4) || (MaxBitCount == 8))
        {
            SavebitCount = MaxBitCount;
        }
    }

    // compute size of bitmap
    if (SavebitCount == 16)
    {
        SavebitCount = 24;
    }
    if (SavebitCount == 32)
    {
        SavebitCount = 24;
    }

    WORD size;
    if (SavebitCount <= 8)
    {
        size = sizeof(BITMAPINFOHEADER) + ((1 << SavebitCount) * sizeof(RGBQUAD));
    }
    else
    {
        size = sizeof(BITMAPINFOHEADER);
    }

    BITMAPINFO * SaveBitmapInfo = (BITMAPINFO *) new char[size];

    SaveBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    SaveBitmapInfo->bmiHeader.biWidth  = g_PrinterAreaXHigh - g_PrinterAreaXLow;
    SaveBitmapInfo->bmiHeader.biHeight = g_PrinterAreaYHigh - g_PrinterAreaYLow;
    SaveBitmapInfo->bmiHeader.biPlanes = 1;
    SaveBitmapInfo->bmiHeader.biBitCount = SavebitCount;
    SaveBitmapInfo->bmiHeader.biCompression = BI_RGB;
    SaveBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
    SaveBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
    SaveBitmapInfo->bmiHeader.biClrUsed = 0;
    SaveBitmapInfo->bmiHeader.biClrImportant = 0;

    SaveBitmapInfo->bmiHeader.biSizeImage = ((((SaveBitmapInfo->bmiHeader.biWidth * SaveBitmapInfo->bmiHeader.biBitCount) + 31) / 32) * 4) * SaveBitmapInfo->bmiHeader.biHeight;

    // allocate space for the raw DIB data
    unsigned char * bitsPtr = new unsigned char[SaveBitmapInfo->bmiHeader.biSizeImage];
    memset(bitsPtr, 0x00, SaveBitmapInfo->bmiHeader.biSizeImage);

    // if palette yank it in 
    HPALETTE oldPalette2;
    if (EnablePalette)
    {
        oldPalette2 = SelectPalette(screen, ThePalette, FALSE);
        RealizePalette(screen);
    }

    // if custom then use custom dimensions
    if (!IsActiveAreaOneToOneWithScreen())
    {
        HBITMAP areaMemoryBitMap = CreateCompatibleBitmap(
            screen,
            g_PrinterAreaXHigh - g_PrinterAreaXLow,
            g_PrinterAreaYHigh - g_PrinterAreaYLow);

        if (!areaMemoryBitMap)
        {
            status = OUT_OF_MEM;
        }
        else
        {
            HDC     memoryDC          = GetMemoryDeviceContext();
            HBITMAP savedMemoryBitmap = (HBITMAP) SelectObject(memoryDC, MemoryBitMap);

            HDC     areaMemoryDC          = CreateCompatibleDC(screen);
            HBITMAP savedAreaMemoryBitmap = (HBITMAP) SelectObject(areaMemoryDC, areaMemoryBitMap);

            BitBlt(
                areaMemoryDC,
                0,
                0,
                g_PrinterAreaXHigh - g_PrinterAreaXLow,
                g_PrinterAreaYHigh - g_PrinterAreaYLow,
                memoryDC,
                +g_PrinterAreaXLow  + xoffset,
                -g_PrinterAreaYHigh + yoffset,
                SRCCOPY);

            SelectObject(areaMemoryDC, savedAreaMemoryBitmap);
            DeleteDC(areaMemoryDC);

            SelectObject(memoryDC, savedMemoryBitmap);

            // convert logo bitmap to raw DIB in bitsPtr
            GetDIBits(
                screen,
                areaMemoryBitMap,
                0,
                g_PrinterAreaYHigh - g_PrinterAreaYLow,
                bitsPtr,
                SaveBitmapInfo,
                DIB_RGB_COLORS);

            DeleteObject(areaMemoryBitMap);
        }
    }
    else
    {
        // else do whole thing
        // convert logo bitmap to raw DIB in bitsPtr
        GetDIBits(
            screen,
            MemoryBitMap,
            0,
            BitMapHeight,
            bitsPtr,
            SaveBitmapInfo,
            DIB_RGB_COLORS);
    }

    // restore some of the resources
    if (EnablePalette)
    {
        SelectPalette(screen, oldPalette2, FALSE);
    }

    DeleteDC(screen);

    // build header
    if (status == SUCCESS)
    {
        BITMAPFILEHEADER BitmapFileHeader;
        BitmapFileHeader.bfType = 19778;
        BitmapFileHeader.bfSize = size + sizeof(BITMAPFILEHEADER) + (int) (SaveBitmapInfo->bmiHeader.biWidth * SaveBitmapInfo->bmiHeader.biHeight * (SavebitCount / 8));
        BitmapFileHeader.bfReserved1 = 0;
        BitmapFileHeader.bfReserved2 = 0;
        BitmapFileHeader.bfOffBits = size + sizeof(BITMAPFILEHEADER);

        // write headers
        fwrite(&BitmapFileHeader, sizeof(char), sizeof(BitmapFileHeader), File);
        fwrite(SaveBitmapInfo, sizeof(char), size, File);

        // write out raw DIB data to file
        fwrite(bitsPtr, sizeof(char), SaveBitmapInfo->bmiHeader.biSizeImage, File);
    }

    delete [] bitsPtr;
    delete SaveBitmapInfo;

    return status;
}

ERR_TYPES DumpBitmapFile(PCSTR Filename, int MaxBitCount)
{
    // open and check if ok
    FILE* file = fopen(Filename, "wb");
    if (file == NULL)
    {
        return IMAGE_BMP_OPEN_FAILED;
    }

    // Load hour-glass cursor.
    HCURSOR oldCursor = ::SetCursor(hCursorWait);

    // do it and if error then let user know 
    ERR_TYPES status = WriteDIB(file, MaxBitCount);

    // Restore the arrow cursor
    ::SetCursor(oldCursor);

    int rval = fclose(file);
    if (rval != 0)
    {
        status = IMAGE_BMP_WRITE_FAILED;
    }

    return status;
}


// Attempt to open a Windows 3.0 device independent bitmap
bool OpenDIB(FILE* File, DWORD &dwPixelWidth, DWORD &dwPixelHeight)
{
    // get header 
    rewind(File);

    BITMAPFILEHEADER BitmapFileHeader;
    fread(&BitmapFileHeader, sizeof(char), sizeof(BitmapFileHeader), File);

    // bfOffbits should be equal to BitmapInfoHeader
    BITMAPINFO * ReadBitmapInfo = (BITMAPINFO *) new char[BitmapFileHeader.bfOffBits - sizeof(BitmapFileHeader)];
    fread(ReadBitmapInfo, sizeof(char), BitmapFileHeader.bfOffBits - sizeof(BitmapFileHeader), File);

    // save some typing 
    DWORD NewPixelWidth  = ReadBitmapInfo->bmiHeader.biWidth;
    DWORD NewPixelHeight = ReadBitmapInfo->bmiHeader.biHeight;

    if (dwPixelWidth)
    {
        // do what the spec says 
        if (ReadBitmapInfo->bmiHeader.biClrUsed == 0)
        {
            ReadBitmapInfo->bmiHeader.biClrUsed = 1 << ReadBitmapInfo->bmiHeader.biBitCount;
        }

        /* only allow bitcount equal to display capability */
        WORD ReadbitCount = ReadBitmapInfo->bmiHeader.biBitCount;

        // if palette load up palette from bitmap color table
        if (EnablePalette)
        {
            if (ReadbitCount == 8)
            {
                for (DWORD i = 0; i < ReadBitmapInfo->bmiHeader.biClrUsed; i++)
                {
                    LoadColor(
                        ReadBitmapInfo->bmiColors[i].rgbRed,
                        ReadBitmapInfo->bmiColors[i].rgbGreen,
                        ReadBitmapInfo->bmiColors[i].rgbBlue);
                }
            }
            else
            {
                // fill palette with a wide range
                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        for (int k = 0; k < 5; k++)
                        {
                            LoadColor(i * 42, j * 42, k * 42);
                        }
                    }
                }
            }
        }


        // compute image size if not set
        if (ReadBitmapInfo->bmiHeader.biSizeImage == 0)
        {
            long longWidth = (((NewPixelWidth * ReadbitCount) + 31) / 32) * 4;

            ReadBitmapInfo->bmiHeader.biSizeImage = longWidth * NewPixelHeight;
        }

        // pack and allocate
        unsigned char * bitsPtr = new unsigned char[ReadBitmapInfo->bmiHeader.biSizeImage];
        memset(bitsPtr, 0x00, ReadBitmapInfo->bmiHeader.biSizeImage);

        // read the file into the bitmap
        fread(bitsPtr, sizeof(char), ReadBitmapInfo->bmiHeader.biSizeImage, File);

        // Create DC comaptible with screen 
        HDC screen   = GetScreenDeviceContext();
        HDC memoryDC = GetMemoryDeviceContext();

        HDC DCHandle = CreateCompatibleDC(screen);

        HPALETTE oldPalette  = NULL;
        HPALETTE oldPalette2 = NULL;

        // if palette yank it
        if (EnablePalette)
        {
            oldPalette = SelectPalette(memoryDC, ThePalette, FALSE);
            RealizePalette(memoryDC);

            oldPalette2 = SelectPalette(screen, ThePalette, FALSE);
            RealizePalette(screen);
        }

        // now create the bitmap with the bits just loaded
        HBITMAP NewBitmapHandle = CreateDIBitmap(
            screen,
            &ReadBitmapInfo->bmiHeader,
            CBM_INIT,
            bitsPtr,
            ReadBitmapInfo,
            0);

        // now dump the bits 
        delete [] bitsPtr;
      
        if (EnablePalette)
        {
            SelectPalette(screen, oldPalette2, FALSE);
        }

        // now that things are clean we can check if we are ok 

        if (!NewBitmapHandle)
        {
            return false;
        }

        // We've now made a bonefide bitmap. 
        // But we want to copy it into the existing backing store.
        if (EnablePalette)
        {
            oldPalette2 = SelectPalette(DCHandle, ThePalette, FALSE);
            RealizePalette(DCHandle);
        }

        HBITMAP oldBitmap  = (HBITMAP) SelectObject(memoryDC, MemoryBitMap);
        HBITMAP oldBitmap2 = (HBITMAP) SelectObject(DCHandle, NewBitmapHandle);

        /* if either dimension is more than half then put in corner */
        if ((NewPixelWidth > (BitMapWidth / 2)) || (NewPixelHeight > (BitMapHeight / 2)))
        {
            BitBlt(
                memoryDC,
                0,
                0,
                NewPixelWidth,
                NewPixelHeight,
                DCHandle,
                0,
                0,
                SRCCOPY);
        }
        else
        {
            /* else put at turtle */
            POINT dest;

            if (current_mode == perspectivemode)
            {
                VECTOR from3d;

                from3d.x = g_SelectedTurtle->Position.x / WorldWidth;
                from3d.y = g_SelectedTurtle->Position.y / WorldHeight;
                from3d.z = g_SelectedTurtle->Position.z / WorldDepth;

                if (!ThreeD.TransformPoint(from3d, dest))
                {
                    return true;
                }
            }
            else
            {
                dest.x = g_round(g_SelectedTurtle->Position.x);
                dest.y = g_round(g_SelectedTurtle->Position.y);
            }

            BitBlt(
                memoryDC,
                +dest.x + xoffset,
                -dest.y + yoffset + LL - NewPixelHeight,
                NewPixelWidth,
                NewPixelHeight, 
                DCHandle, 
                0, 
                0, 
                SRCCOPY);
        }

        // return resources
        if (EnablePalette)
        {
            SelectPalette(memoryDC, oldPalette, FALSE);
            SelectPalette(DCHandle, oldPalette2, FALSE);
        }

        SelectObject(memoryDC, oldBitmap);
        SelectObject(DCHandle, oldBitmap2);
        DeleteDC(DCHandle);

        DeleteObject(NewBitmapHandle);
    }

    delete [] ReadBitmapInfo;

    dwPixelWidth  = NewPixelWidth;
    dwPixelHeight = NewPixelHeight;
    return true;
}

ERR_TYPES LoadBitmapFile(LPCSTR Filename, DWORD &dwPixelWidth, DWORD &dwPixelHeight)
{
    // Test if Filename is a Windows 3.0 DIB bitmap and if so read it

    // open then check if open 
    FILE* file = fopen(Filename, "rb");
    if (file == NULL)
    {
        return IMAGE_BMP_OPEN_FAILED;
    }

    // check if valid bitmap
    ERR_TYPES status = SUCCESS;
    fseek(file, 14, SEEK_SET);

    long TestWin30Bitmap = 0;
    fread(&TestWin30Bitmap, sizeof(char), sizeof(TestWin30Bitmap), file);
    if (TestWin30Bitmap == 40)
    {
        // Load hour-glass cursor.
        HCURSOR oldCursor = ::SetCursor(hCursorWait);

        // if loaded ok then invalidate to display 
        if (OpenDIB(file, dwPixelWidth, dwPixelHeight))
        {
            ::InvalidateRect(GetScreenWindow(), NULL, TRUE);
        }
        else
        {
            status = IMAGE_BMP_CREATE_FAILED;
        }

        // Restore the arrow cursor.
        ::SetCursor(oldCursor);
    }
    else
    {
        // not a bitmap
        status = IMAGE_BMP_INVALID;
    }
    fclose(file);

    return status;
}

void PaintToScreenWindow(HDC PaintDC, const RECT & PaintRect)
{
    /*
      This is a compromise between speed and memory (as is most code).
      All drawing is written to the backing store 1 to 1 even when zoomed.
      When zoomed all drawing and painting is scaled to the display on the fly.
      Painting can be a bit slow while zoomed. It also can be inaccurate when
      mixing scaled painting and scaled drawing. Printing is never zoomed.
      User can use Bitfit if he/she wants data scaled.

      Must of rewrote this routine 20 times, at least.
    */

    // grab the client area's backing store (a bitmap)
    HDC memoryDC = GetMemoryDeviceContext();

    HBITMAP oldBitmap = (HBITMAP) SelectObject(memoryDC, MemoryBitMap);

    HPALETTE oldPalette  = NULL;
    HPALETTE oldPalette2 = NULL;

    /* if palette allocate it */

    if (EnablePalette)
    {
        oldPalette = SelectPalette(PaintDC, ThePalette, FALSE);
        RealizePalette(PaintDC);

        oldPalette2 = SelectPalette(memoryDC, ThePalette, FALSE);
        RealizePalette(memoryDC);
    }

    HBRUSH whiteBrush = (HBRUSH) GetStockObject(WHITE_BRUSH);

    if (!zoom_flag)
    {
        // fill the part to the right of the screen.
        if (BitMapWidth < PaintRect.right)
        {
            RECT toFill;
            toFill.left   = BitMapWidth;
            toFill.right  = PaintRect.right;
            toFill.top    = 0;
            toFill.bottom = BitMapHeight;

            FillRect(PaintDC, &toFill, whiteBrush);
        }
        // fill the part below the screen.
        if (BitMapHeight < PaintRect.bottom)
        {
            RECT toFill;
            toFill.left   = PaintRect.left;
            toFill.right  = PaintRect.right;
            toFill.top    = BitMapHeight;
            toFill.bottom = PaintRect.bottom;

            FillRect(PaintDC, &toFill, whiteBrush);
        }

        // The zoom is 1:1.  Just do a 1:1 BLIT (no scaling).
        BitBlt(
            PaintDC,
            PaintRect.left,
            PaintRect.top,
            PaintRect.right  - PaintRect.left,
            PaintRect.bottom - PaintRect.top,
            memoryDC,
            PaintRect.left,
            PaintRect.top,
            SRCCOPY);
    }
    else
    {
        // We are zoomed in.  Compute scaling and then display
        if (g_OsVersionInformation.dwPlatformId == VER_PLATFORM_WIN32_NT)
        {
            SetStretchBltMode(PaintDC, HALFTONE);
        }
        else
        {
            // HALFTONE is not supported on Win 95/98/ME
            SetStretchBltMode(PaintDC, COLORONCOLOR);
        }

        FLONUM sourceRectLeft   = PaintRect.left;
        FLONUM sourceRectTop    = PaintRect.top;
        FLONUM sourceRectRight  = PaintRect.right;
        FLONUM sourceRectBottom = PaintRect.bottom;

        // Expand the source rectangle a little bit based zoom factor 
        // (rounding to the nearest integer, as necessary)
        const FLONUM inflateIncrement = (the_zoom+0.5)*2.0;
        sourceRectLeft   -= inflateIncrement;
        sourceRectTop    -= inflateIncrement;
        sourceRectRight  += inflateIncrement;
        sourceRectBottom += inflateIncrement;

        FLONUM scaledSourceRectLeft   = sourceRectLeft   / the_zoom;
        FLONUM scaledSourceRectTop    = sourceRectTop    / the_zoom;
        FLONUM scaledSourceRectRight  = sourceRectRight  / the_zoom;
        FLONUM scaledSourceRectBottom = sourceRectBottom / the_zoom;

        // fill the part to the right of the screen.
        if (BitMapWidth < scaledSourceRectRight)
        {
            RECT toFill;
            toFill.left   = BitMapWidth * the_zoom;
            toFill.right  = sourceRectRight;
            toFill.top    = 0;
            toFill.bottom = BitMapHeight * the_zoom;

            FillRect(PaintDC, &toFill, whiteBrush);
        }
        // fill the part below the screen.
        if (BitMapHeight < scaledSourceRectBottom)
        {
            RECT toFill;
            toFill.left   = sourceRectLeft;
            toFill.right  = sourceRectRight;
            toFill.top    = BitMapHeight * the_zoom;
            toFill.bottom = sourceRectBottom;

            FillRect(PaintDC, &toFill, whiteBrush);
        }

        // Make sure that none of rectangle's borders are off-screen
        // after we inflated it.
        RECT sourceRect;
        sourceRect.left   = (int) (min(max(scaledSourceRectLeft,   0.0), (double)BitMapWidth));
        sourceRect.top    = (int) (min(max(scaledSourceRectTop,    0.0), (double)BitMapHeight));
        sourceRect.right  = (int) (min(max(scaledSourceRectRight,  0.0), (double)BitMapWidth));
        sourceRect.bottom = (int) (min(max(scaledSourceRectBottom, 0.0), (double)BitMapHeight));

        RECT destRect;
        destRect.left   = sourceRect.left   * the_zoom;
        destRect.top    = sourceRect.top    * the_zoom;
        destRect.right  = sourceRect.right  * the_zoom;
        destRect.bottom = sourceRect.bottom * the_zoom;

        StretchBlt(
            PaintDC,
            destRect.left,
            destRect.top,
            destRect.right  - destRect.left,
            destRect.bottom - destRect.top,
            memoryDC,
            sourceRect.left,
            sourceRect.top,
            sourceRect.right  - sourceRect.left,
            sourceRect.bottom - sourceRect.top,
            SRCCOPY);
    }

    // restore resources
    if (EnablePalette)
    {
        SelectPalette(memoryDC, oldPalette2, FALSE);
        SelectPalette(PaintDC, oldPalette, FALSE);
    }

    SelectObject(memoryDC, oldBitmap);

    // draw the turtles on top of the image
    SetROP2(PaintDC, R2_NOT);

    for (int j = 0; j <= g_MaxTurtle; j++)
    {
        if (g_Turtles[j].IsShown)
        {
            if (g_Turtles[j].BitmapRasterMode)
            {
                turtlepaste(j);
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    if (g_Turtles[j].Points[i].bValid)
                    {
                        MoveToEx(
                            PaintDC,
                            g_Turtles[j].Points[i].from.x * the_zoom,
                            g_Turtles[j].Points[i].from.y * the_zoom,
                            0);

                        LineTo(
                            PaintDC,
                            g_Turtles[j].Points[i].to.x * the_zoom,
                            g_Turtles[j].Points[i].to.y * the_zoom);
                    }
                }
            }
        }
    }
}


void checkwindow(int *x, int *y, int *w, int *h)
{
    RECT workingArea;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workingArea, 0);

    int minX      = workingArea.left;
    int minY      = workingArea.top;
    int maxWidth  = workingArea.right  - workingArea.left;
    int maxHeight = workingArea.bottom - workingArea.top;

    // sanity check window coordinates
    if (*x < minX)
    {
        *x = minX;
    }
    if (*y < minY) 
    {
        *y = minY;
    }
    if (*w > maxWidth) 
    {
        *w = maxWidth;
    }
    if (*h > maxHeight) 
    {
        *h = maxHeight;
    }

    if (*x + *w > workingArea.right) 
    {
        *x = workingArea.right - *w;
    }
    if (*y + *h > workingArea.bottom)
    {
        *y = workingArea.bottom - *h;
    }
}

NODE *leventcheck(NODE *)
{
    // checkqueue();

    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return Unbound;
}

// function that processes our own queued events 
void checkqueue()
{
    while (callthing * thing = calllists.get())
    {
        bool    save_yield_flag   = yield_flag;
        FIXNUM  save_value_status = g_ValueStatus;

        calllists.zap();
        switch (thing->kind)
        {
        case EVENTTYPE_Mouse:
            // mouse event must not yield while processing
            yield_flag = false;
            mouse_posx = thing->arg1;
            mouse_posy = thing->arg2;
            do_execution(thing->func);
            break;

          case EVENTTYPE_Keyboard:
              // keyboard event must not yield while processing
              yield_flag = false;
              keyboard_value = thing->arg1;
              do_execution(thing->func);
              break;

          case EVENTTYPE_YieldFunction:
              // Button, timer or other event ok to yield while processing
              do_execution(thing->func);
              break;

          case EVENTTYPE_NoYieldFunction:
              // Scrollbar, MCI, Net, timer or other event must not yield while processing
              yield_flag = false;
              do_execution(thing->func);
              break;

          case EVENTTYPE_NetworkReceiveReady:
              // Network events must not yield while processing
              yield_flag = false;

              // use the new value
              thing->networkconnection->SetLastPacketReceived(thing->networkpacket);
              thing->networkpacket = NULL;

              do_execution(thing->func);
              break;

        default:
            assert(0 && "bad callthing type");
            break;
        }

        delete thing;

        yield_flag    = save_yield_flag;
        g_ValueStatus = save_value_status;
    }
}

/* function to dump the queue */

void emptyqueue()
{
    while (callthing * thing = calllists.get())
    {
        calllists.zap();

        delete thing;
    }
}
