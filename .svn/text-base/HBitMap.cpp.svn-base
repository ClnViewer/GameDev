/*
    MIT License

    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/GameDev

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sub license, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */

#define _WIN32_WINNT 0x0501
#include "BitMap.h"
#include "Wnd.h"

/* Debug output Only */
#include <stdio.h>
#include <string.h>

HBITMAP DLL_EXPORT hbmpCaptureWindow(HWND hwnd, POINT *p)
{
    HDC hdcs = NULL,
        hdcc = NULL;
    HBITMAP hbmp = NULL;

    do
    {
        int w, h;
        HGDIOBJ hobj;
        RECT crect = { 0, 0, 0, 0 };
        if (!GetClientRect(hwnd, &crect))
            break;

        w = (crect.right - crect.left);
        h = (crect.bottom - crect.top);

        if ((p) && ((w != p->x) || (h != p->y)))
        {
            int x = ((p->x > w) ? (p->x - w) : (w - p->x)),
                y = ((p->y > h) ? (p->y - h) : (h - p->y));

            if (!MoveWindow(hwnd, x, y, p->x, p->y, TRUE))
                break;
            Sleep(100);
            return hbmpCaptureWindow(hwnd, p);
        }

        if (
            ((hdcs = GetDC(hwnd)) == NULL) ||
            ((hdcc = CreateCompatibleDC(hdcs)) == NULL) ||
            ((hbmp = CreateCompatibleBitmap(hdcs, w, h)) == NULL)
        )
            break;

        hobj = SelectObject(hdcc, hbmp);
        if (
            (hobj == NULL) ||
            (hobj == HGDI_ERROR) ||
            (!BitBlt(hdcc, 0, 0, w, h, hdcs, 0, 0, SRCCOPY))
        )
        {
            DeleteObject(hbmp);
            hbmp = NULL;
        }
    }
    while (0);

    if (hdcc != NULL)
        DeleteDC(hdcc);
    if (hdcs != NULL)
        ReleaseDC(hwnd, hdcs);

    return hbmp;
}

BOOL DLL_EXPORT hbmpGrayscale(HBITMAP hbmp, BOOL isbw)
{
    BOOL ret = FALSE;
    HDC hdcc = NULL;
    BYTE *bmppix = NULL;

    if (hbmp == NULL)
        return ret;

    do
    {
        int st;
        BITMAP bm;
        BITMAPINFO bmpi;

        GetObject(hbmp, sizeof(bm), &bm);
        if (bm.bmBitsPixel < 24)
            break;

        if ((hdcc = CreateCompatibleDC(NULL)) == NULL)
            break;

        ZeroMemory(&bmpi, sizeof(BITMAPINFO));

        bmpi.bmiHeader.biSize = sizeof(bmpi.bmiHeader);
        bmpi.bmiHeader.biWidth = bm.bmWidth;
        bmpi.bmiHeader.biHeight = bm.bmHeight;
        bmpi.bmiHeader.biPlanes = 1;
        bmpi.bmiHeader.biBitCount = bm.bmBitsPixel;
        bmpi.bmiHeader.biCompression = BI_RGB;
        bmpi.bmiHeader.biSizeImage = (((bm.bmWidth * bm.bmBitsPixel + 31) / 32) * 4 * bm.bmHeight);

        st = (bm.bmWidth + (bm.bmWidth * bm.bmBitsPixel / 8) % 4);
        bmppix = new BYTE[bmpi.bmiHeader.biSizeImage];

        if (!GetDIBits(hdcc, hbmp, 0, bm.bmHeight, bmppix, &bmpi, DIB_RGB_COLORS))
            break;

#       pragma omp parallel for schedule(dynamic)
        for(int y = 0; y < bm.bmHeight; y++)
        {
            for(int x = 0; x < st; x++)
            {
                int i = ((x + y * st) * bm.bmBitsPixel / 8);
                BYTE gray = ((isbw) ?
                             (
                                 (
                                     (bmppix[i+0] > 127U) ||
                                     (bmppix[i+1] > 127U) ||
                                     (bmppix[i+2] > 127U)
                                 )
                                 ? static_cast<BYTE>(0xFF) : static_cast<BYTE>(0x0)
                             ):
                             BYTE(0.1 * bmppix[i+0] + 0.6 * bmppix[i+1] + 0.3 * bmppix[i+2])
                            );
                bmppix[i+0] = bmppix[i+1] = bmppix[i+2] = gray;
                // AlfaCh bmppix[i+3] = ((isbw) ? 0x0 : bmppix[i+3]);
            }
        }
        SetDIBits(hdcc, hbmp, 0, bm.bmHeight, bmppix, &bmpi, DIB_RGB_COLORS);
        ret = TRUE;
    }
    while (0);

    if (hdcc != NULL)
        DeleteDC(hdcc);
    if (bmppix != NULL)
        delete [] bmppix;

    return ret;
}

BOOL DLL_EXPORT hbmpSave(HBITMAP hbmp, const LPWSTR fname)
{
    BOOL ret = FALSE;
    HDC hdcc = NULL;
    BYTE *bmppix = NULL;

    if (hbmp == NULL)
        return ret;

    BITMAP bm;
    BITMAPINFO bmpi;
    BITMAPFILEHEADER bmph;
    ZeroMemory(&bmpi, sizeof(BITMAPINFO));
    ZeroMemory(&bmph, sizeof(BITMAPFILEHEADER));
    GetObject(hbmp, sizeof(BITMAP), &bm);

    bmpi.bmiHeader.biSize = sizeof(bmpi.bmiHeader);
    bmpi.bmiHeader.biWidth = bm.bmWidth;
    bmpi.bmiHeader.biHeight = bm.bmHeight;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 24;
    bmpi.bmiHeader.biCompression = BI_RGB;

    UINT bmsize;
    int bmppad = ((bm.bmWidth * 3) % 4);
    if (bmppad != 0)
        bmppad = 4 - bmppad;

    bmsize = static_cast<UINT>((bm.bmWidth * 3 + bmppad) * bm.bmHeight);

    bmph.bfOffBits = static_cast<DWORD>(sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));
    bmph.bfSize = static_cast<DWORD>(
                      bmsize
                      + sizeof(BITMAPFILEHEADER)
                      + sizeof(BITMAPINFOHEADER)
                  );
    bmph.bfType = 0x4D42;
    bmppix = new BYTE[bmsize];

    do
    {
        HGDIOBJ hobj;
        HANDLE fout;

        if ((hdcc = CreateCompatibleDC(NULL)) == NULL)
            break;

        hobj = SelectObject(hdcc, hbmp);
        if (
            (hobj == NULL) ||
            (hobj == HGDI_ERROR)
        )
            break;

        if (!GetDIBits(hdcc, hbmp, 0, bm.bmHeight, bmppix, &bmpi, DIB_RGB_COLORS))
            break;

        if ((fout = CreateFileW(fname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == NULL)
            break;

        DWORD sz = 0;
        WriteFile(fout, static_cast<void*>(&bmph), sizeof(BITMAPFILEHEADER), &sz, NULL);
        WriteFile(fout, static_cast<void*>(&bmpi.bmiHeader), sizeof(BITMAPINFOHEADER), &sz, NULL);
        WriteFile(fout, static_cast<void*>(bmppix), (bm.bmWidth * 3 + bmppad) * bm.bmHeight, &sz, NULL);
        CloseHandle(fout);
        ret = TRUE;
    }
    while (0);

    delete[] bmppix;

    if (hdcc != NULL)
        DeleteDC(hdcc);

    return ret;
}

HBITMAP DLL_EXPORT hbmpFromFile(const LPWSTR fname, POINT *point)
{
    HANDLE hf = NULL;
    HBITMAP hbmp = NULL;

    do
    {
        BYTE *bit;
        DWORD sz, rsz;

        if (!(hf = CreateFileW(fname, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL)))
            break;

        if ((sz = GetFileSize(hf, NULL)) == INVALID_FILE_SIZE)
            break;

        if ((bit = static_cast<PBYTE>(LocalAlloc(LMEM_FIXED, (sz * sizeof(BYTE))))) == NULL)
            break;

        if ((!ReadFile(hf, bit, sz, &rsz, NULL)) || (sz != rsz))
        {
            LocalFree(bit);
            break;
        }
        hbmp = hbmpFromBuffer(bit, point);
        LocalFree(bit);
    }
    while (0);

    if (hf)
        CloseHandle(hf);

    return hbmp;
}
HBITMAP DLL_EXPORT hbmpFromBuffer(BYTE *buf, POINT *point)
{
    if (!buf)
        return NULL;

    HDC               hdc  = NULL;
    HBITMAP           hbmp = NULL;
    BITMAPFILEHEADER *bfh  = reinterpret_cast<BITMAPFILEHEADER*>(&buf[0]);
    BITMAPINFO       *bi   = reinterpret_cast<BITMAPINFO*>(&buf[sizeof(BITMAPFILEHEADER)]);
    BITMAPINFOHEADER *bih  = reinterpret_cast<BITMAPINFOHEADER*>(&bi->bmiHeader);
    unsigned char    *bit  = &buf[bfh->bfOffBits];

    if (point)
    {
        point->x = bih->biWidth;
        point->y = bih->biHeight;
    }

#   if defined(__HBMP_DEBUG)
    printf("\nbfOffBits=%ld = [(-1)%X (0)%X (+1)%X]\n", bfh->bfOffBits, buf[bfh->bfOffBits - 1], buf[bfh->bfOffBits], buf[bfh->bfOffBits + 1]);
    printf("biWidth=%ld, biHeight=%ld\n", bih->biWidth, bih->biHeight);
    printf("biCompression=%ld/%d, biBitCount=%d\n", bih->biCompression, BI_RGB, bih->biBitCount);
    printf("biSize=%ld, biSizeImage=%ld\n", bih->biSize, bih->biSizeImage);
    printf("biPlanes=%d\n", bih->biPlanes);
#   endif

    do
    {
        if (!(hdc = CreateCompatibleDC(NULL)))
            break;

        hbmp = CreateDIBitmap(
                   hdc,
                   bih,
                   CBM_INIT,
                   static_cast<void*> (bit),
                   bi,
                   DIB_RGB_COLORS
               );
    }
    while (0);

    if (hdc)
        DeleteDC(hdc);

    return hbmp;
}

HBITMAP DLL_EXPORT hbmpGetWindow(const LPWSTR wclass, const LPWSTR wname, BOOL isbw, POINT *p, HWND *hwnd)
{
    HBITMAP hbmp = NULL;

    do
    {
        if (
            ((wclass == NULL) || (hwnd == NULL)) ||
            ((*hwnd = wndChildLastElement(NULL, wclass, wname)) == NULL) ||
            (!IsWindow(*hwnd)) ||
            (!wndActivateWindow(*hwnd, FALSE)) ||
            ((hbmp = hbmpCaptureWindow(*hwnd, p)) == NULL)
        )
            break;

        if (!hbmpGrayscale(hbmp, isbw))
        {
            DeleteObject(hbmp);
            hbmp = NULL;
        }
    }
    while (0);

    return hbmp;
}

void DLL_EXPORT hbmpFree(HBITMAP hbmp)
{
    if (hbmp != NULL)
        DeleteObject(hbmp);
}
