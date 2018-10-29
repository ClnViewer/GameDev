#define _WIN32_WINNT 0x0501
#include "BitMap.h"
#include "Wnd.h"

/* Debug output Only */
//#include <stdio.h>
//#include <string.h>

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

    int bmppad = ((bm.bmWidth * 3) % 4);
    if (bmppad != 0)
        bmppad = 4 - bmppad;

    bmph.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);
    bmph.bfSize = (DWORD)(
                      ((bm.bmWidth * 3 + bmppad) * bm.bmHeight)
                      + sizeof(BITMAPFILEHEADER)
                      + sizeof(BITMAPINFOHEADER)
                  );
    bmph.bfType = 0x4D42;
    bmppix = new BYTE[(bm.bmWidth * 3 + bmppad) * bm.bmHeight];

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
        WriteFile(fout, (LPSTR)&bmph, sizeof(BITMAPFILEHEADER), &sz, NULL);
        WriteFile(fout, (LPSTR)&bmpi.bmiHeader, sizeof(BITMAPINFOHEADER), &sz, NULL);
        WriteFile(fout, (LPSTR)bmppix, (bm.bmWidth * 3 + bmppad) * bm.bmHeight, &sz, NULL);
        CloseHandle(fout);
        ret = TRUE;
    }
    while (0);

    delete[] bmppix;

    if (hdcc != NULL)
        DeleteDC(hdcc);

    return ret;
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
