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
#include <windows.h>

#include <iostream>
using namespace std;

#define __NELE(a) (sizeof(a) / sizeof(a[0]))

HBITMAP hbmpCaptureWindow(HWND hwnd)
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

BOOL hbmpGrayscale(HBITMAP hbmp, BOOL isbw)
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
                                 ? 0xFF : 0x0
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

BOOL hbmpSave(HBITMAP hbmp, const LPWSTR fname)
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

HBITMAP hbmpGetWindow(const LPWSTR name, BOOL isbw, HWND *hwnd)
{
    HBITMAP hbmp = NULL;

    do
    {
        if (
            ((name == NULL) || (hwnd == NULL)) ||
            ((*hwnd = FindWindowW(0, name)) == NULL) ||
            ((hbmp = hbmpCaptureWindow(*hwnd)) == NULL)
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

void screenshot_window(HWND hwnd, const LPWSTR fname)
{
    int w, h;
    HDC hdcs = NULL,
        hdcc = NULL;
    HBITMAP hbmp = NULL;

    if (hwnd == NULL)
        return;

    //SetForegroundWindow(hwnd);

    do
    {
        RECT crect = { 0, 0, 0, 0 };
        if (!GetClientRect(hwnd, &crect))
            return;

        w = (crect.right - crect.left);
        h = (crect.bottom - crect.top);

        hdcs = GetDC(hwnd);
        hdcc = CreateCompatibleDC(hdcs);
        hbmp = CreateCompatibleBitmap(hdcs, w, h);
        SelectObject(hdcc, hbmp);

        BitBlt(hdcc, 0, 0, w, h, hdcs, 0, 0, SRCCOPY);

        BITMAPINFO bmpi;
        BITMAPFILEHEADER bmph;
        ZeroMemory(&bmpi, sizeof(BITMAPINFO));
        ZeroMemory(&bmph, sizeof(BITMAPFILEHEADER));

        bmpi.bmiHeader.biSize = sizeof(bmpi.bmiHeader);
        bmpi.bmiHeader.biWidth = w;
        bmpi.bmiHeader.biHeight = h;
        bmpi.bmiHeader.biPlanes = 1;
        bmpi.bmiHeader.biBitCount = 24;
        bmpi.bmiHeader.biCompression = BI_RGB;

        int bmppad = ((w * 3) % 4);
        if (bmppad != 0)
            bmppad = 4 - bmppad;

        bmph.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);
        bmph.bfSize = (DWORD)(w * 3 + bmppad) * h + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        bmph.bfType = 0x4D42;

        BYTE *bmppix = new BYTE[(w * 3 + bmppad) * h];
        GetDIBits(hdcc, hbmp, 0, h, bmppix, &bmpi, DIB_RGB_COLORS);

        do
        {
            HANDLE fout = CreateFileW(fname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (fout == NULL)
                break;

            DWORD sz = 0;
            WriteFile(fout, (LPSTR)&bmph, sizeof(BITMAPFILEHEADER), &sz, NULL);
            WriteFile(fout, (LPSTR)&bmpi.bmiHeader, sizeof(BITMAPINFOHEADER), &sz, NULL);
            WriteFile(fout, (LPSTR)bmppix, (w * 3 + bmppad) * h, &sz, NULL);
            CloseHandle(fout);
        }
        while (0);

        delete[] bmppix;
    }
    while (0);

    if (hbmp != NULL)
        DeleteObject(hbmp);
    if (hdcc != NULL)
        DeleteDC(hdcc);
    if (hdcs != NULL)
        ReleaseDC(hwnd, hdcs);
}


int __main()
{
    HWND hwnd = FindWindowW(0, L"Untitled - Notepad2");
    if (hwnd == NULL)
    {
        return 127;
    }
    screenshot_window(hwnd, (const LPWSTR)L"TestFile1.bmp");

    HBITMAP hbmp = hbmpCaptureWindow(hwnd);
    hbmpGrayscale(hbmp, true);
    hbmpSave(hbmp, (const LPWSTR)L"TestFile2.bmp");
    DeleteObject(hbmp);
    return 0;
}

int ___main()
{
    // Memu MainWindowWindow
    HWND hwnd = NULL;
    HBITMAP hbmp = hbmpGetWindow((const LPWSTR)L"Untitled - Notepad2", false, &hwnd);
    if (hwnd == NULL)
    {
        return 127;
    }
    if (hbmp == NULL)
    {
        return 126;
    }
    hbmpGrayscale(hbmp, true);
    hbmpSave(hbmp, (const LPWSTR)L"TestFile2.bmp");
    DeleteObject(hbmp);
    return 0;
}

HWND wndChildLastElement(HWND hwnd, const LPWSTR ele)
{
    HWND rwnd = NULL;

    if (ele == NULL)
        return rwnd;

    do
    {
        HWND twnd = NULL;

        do
        {
            twnd = FindWindowExW(hwnd, rwnd, ele, NULL);
            if (twnd != NULL)
                rwnd = twnd;
        }
        while (twnd != NULL);
    }
    while (0);

    return rwnd;
}

static HKL __changeLanguage(HWND hwnd, const LPWSTR cpage)
{
    /* EN: 00000409 RU: 00010419 */

    WCHAR wstrk[KL_NAMELENGTH];
    GetKeyboardLayoutNameW(wstrk);
    printf("%ls\n", wstrk);
    //cout << wstrk << endl;

    HKL hkl = LoadKeyboardLayoutW(cpage, KLF_ACTIVATE);
    HKL hold = ActivateKeyboardLayout(hkl, KLF_SETFORPROCESS);
    PostMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, 0, (LPARAM)hkl);

    GetKeyboardLayoutNameW(wstrk);
    printf("%ls\n", wstrk);
    //cout << wstrk << endl;

    PostMessage(hwnd, 0x0050, 2, 0);

    GetKeyboardLayoutNameW(wstrk);
    printf("%ls\n", wstrk);
    //cout << wstrk << endl;

    /*
    PostMessage(hwnd, WM_INPUTLANGCHANGE,
    reinterpret_cast<WPARAM>(0U),
    reinterpret_cast<LPARAM>(hkl)
    );
    */

    /*
    INPUTLANGCHANGE_FORWARD
    LPWSTR gpage = NULL;
    if (GetKeyboardLayoutNameW(gpage))
    {

    }
    */

    //PostMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, 0, (LPARAM)hkl);
    //PostMessage(hwnd, WM_INPUTLANGCHANGE, 0, reinterpret_cast<LPARAM>(hkl));
    return hkl;
}

typedef union
{
    LPARAM lparam;

    struct
    {
        unsigned nRepeatCount : 16;
        unsigned nScanCode : 8;
        unsigned nExtended : 1;
        unsigned nReserved : 4;
        unsigned nContext : 1;
        unsigned nPrev : 1;
        unsigned nTrans : 1;
    } data;
} dataLparam;

typedef struct
{
    wchar_t w;
    UINT key, scan, shift;
} kbLayot;

static kbLayot kbLayot_RU[] =
{
#define __KB_LAYOT(A,B,C,D) { .w = A, .key = B, .scan = C, .shift = D },
#include "KB_table_00010419.h"
};

int _z_main()
{
    // Memu MainWindowWindow
    HWND hwnd = wndChildLastElement(NULL, (const LPWSTR)L"Qt5QWindowIcon");
    if (hwnd == NULL)
    {
        cout << "hwnd is NULL" << endl;
        return 127;
    }
    char szBuff[64] = {0};
    sprintf(szBuff, "%p", hwnd);
    cout << szBuff << endl;

    /*
    HBITMAP hbmp = hbmpCaptureWindow(hwnd);
    hbmpGrayscale(hbmp, true);
    hbmpSave(hbmp, (const LPWSTR)L"TestFile2.bmp");
    DeleteObject(hbmp);
    */

    HKL hkl = __changeLanguage(hwnd,
                               (const LPWSTR)
                               /*L"0x00000409"*/
                               L"00010419"
                              );
    dataLparam ks;
    ZeroMemory(&ks, sizeof(dataLparam));
    ks.data.nRepeatCount = 1;
    ks.data.nScanCode = MapVirtualKeyW(VkKeyScanExW(L'ю', hkl), 0U);

    SendMessageW(hwnd, WM_KEYDOWN, (WPARAM)VK_OEM_PERIOD, reinterpret_cast<LPARAM>(ks.lparam));
    SendMessageW(hwnd, WM_CHAR,
                 reinterpret_cast<WPARAM>((UINT)L'ю'),
                 reinterpret_cast<LPARAM>((LPARAM)1)
                );

    Sleep(10);
    SendMessageW(hwnd, WM_KEYUP, (WPARAM)VK_OEM_PERIOD, (LPARAM)ks.lparam);

    return 0;
}

void __SendKey(HWND hwnd, UINT key, UINT scan, UINT shift)
{
    dataLparam dl;
    ZeroMemory(&dl, sizeof(dataLparam));
    dl.data.nRepeatCount = 1;

    if (shift)
    {
        unsigned long rep = 0,
                      r = (rand() % 10 + 1);

        dl.data.nScanCode = shift;
        dl.data.nPrev = 0;
        do
        {
            PostMessageW(hwnd, WM_KEYDOWN,
                         (WPARAM)VK_SHIFT,
                         (LPARAM)dl.lparam
                        );
            rep++;
            dl.data.nPrev = 1;
        }
        while (rep < r);

        Sleep(50);
        dl.data.nPrev = 0;
    }

    dl.data.nScanCode = scan;
    PostMessageW(hwnd, WM_KEYDOWN,
                 reinterpret_cast<WPARAM>((UINT)key),
                 reinterpret_cast<LPARAM>(dl.lparam)
                );

    dl.data.nRepeatCount = 0;
    dl.data.nPrev = dl.data.nTrans = 1;

    Sleep((DWORD)(rand() % 100 + 1));
    //Sleep(50); // warning! optimal sensitive timeout :)

    PostMessageW(hwnd, WM_KEYUP,
                 reinterpret_cast<WPARAM>((UINT)key),
                 reinterpret_cast<LPARAM>(dl.lparam)
                );
    if (shift)
    {
        dl.data.nScanCode = shift;
        dl.data.nRepeatCount = 1;
        PostMessageW(hwnd, WM_KEYUP,
                     (WPARAM)VK_SHIFT,
                     (LPARAM)dl.lparam
                    );
    }
    Sleep(200);
}

void __SendChar(HWND hwnd, HKL hkl, wchar_t w, UINT pos)
{
    UINT key = 0U, scan = 0U, shift = 0U;

    if ((iswupper(w)) || (!pos))
    {
        do
        {
            if (!iswalpha(w))
                break;

            if (iswupper(w))
            {
                LPWSTR wo;
                wchar_t wc[] = { w, L'\0' };

                wo = CharLowerW((LPWSTR)wc);
                if (wo == NULL)
                    break;

                w = wo[0];
            }
            shift = 0x2a;
        }
        while (0);
    }

    do
    {
        if ((iswpunct(w)) || (iswdigit(w)))
        {
            for (unsigned i = 0; i < __NELE(kbLayot_RU); i++)
            {
                if (kbLayot_RU[i].w == w)
                {
                    key = kbLayot_RU[i].key;
                    scan = kbLayot_RU[i].scan;
                    shift = kbLayot_RU[i].shift;
                    break;
                }
            }
        }

        if ((key) && (scan))
            break;

        if (iswascii(w))
        {
            key = VkKeyScanExW(w, hkl);
            scan = MapVirtualKeyW(key, 0U);
        }
        else if (iswalnum(w))
        {
            key = VK_OEM_PERIOD;
            scan = MapVirtualKeyW(VkKeyScanExW(w, hkl), 0U);
        }

        if ((!key) || (!scan))
            return;
    }
    while (0);

    __SendKey(hwnd, key, scan, shift);
}

void __TestKey(HWND hwnd)
{
    dataLparam dl;
    ZeroMemory(&dl, sizeof(dataLparam));
    dl.data.nRepeatCount = 0;
    dl.data.nExtended = 1;
    dl.data.nScanCode = 0x45;

            PostMessageW(hwnd, WM_KEYDOWN,
                         (WPARAM)VK_NUMLOCK,
                         (LPARAM)dl.lparam
                        );

    dl.data.nRepeatCount = dl.data.nPrev = dl.data.nTrans = 1;

            PostMessageW(hwnd, WM_KEYUP,
                         (WPARAM)VK_NUMLOCK,
                         (LPARAM)dl.lparam
                        );

    dl.data.nExtended = 0;
    dl.data.nPrev = dl.data.nTrans = 0;

    ////
    Sleep((DWORD)(rand() % 100 + 1));

    dl.data.nRepeatCount = 1;
    dl.data.nScanCode = 0x4f;
    PostMessageW(hwnd, WM_KEYDOWN,
                 reinterpret_cast<WPARAM>((UINT)VK_NUMPAD1),
                 reinterpret_cast<LPARAM>(dl.lparam)
                );

    dl.data.nPrev = dl.data.nTrans = 1;

    Sleep((DWORD)(rand() % 100 + 1));

    PostMessageW(hwnd, WM_KEYUP,
                 reinterpret_cast<WPARAM>((UINT)VK_NUMPAD1),
                 reinterpret_cast<LPARAM>(dl.lparam)
                );
}

int main()
{
    wchar_t wwww[] = L"abc.,+-123Петр чайка";
    wchar_t www[] = L"18 is not 22 or yes!";
    wchar_t ww[] = L"ух 1234567890 летять утки, и 22 гуся (!\"№;%:?*()_+=-)";
    wchar_t w[] = L"ух 1234567890 летять утки, и 22 гуся. шли-бы они лесом";

    //unsigned long aaa = wcstoul(L"00000419",NULL,10);
    //cout << aaa << endl;
    //return 0;

    HWND hwnd = wndChildLastElement(NULL, (const LPWSTR)L"Qt5QWindowIcon");
    if (hwnd == NULL)
    {
        cout << "hwnd is NULL" << endl;
        return 127;
    }
    char szBuff[64] = {0};
    sprintf(szBuff, "%p", hwnd);
    cout << szBuff << endl;

    HKL hkl = __changeLanguage(hwnd,
                               (const LPWSTR)
                               /*L"00000409"*/
                               /*L"00000419"*/
                               /*L"00010419"*/
                               L"00010419"
                              );
    __TestKey(hwnd);
    Sleep(1000);
    return 0;

    //  SendMessageTimeout (HWND_BR OADCAST, WM _SETTINGCH ANGE, 0, int eger (point er (s1)), SM TO_NORMAL,1000, c1);
    //  SendMessageTimeout(hWnd, WM_COPYDATA, IntPtr.Zero, ref cds, 0x0000, 500);

    /*
    DWORD Result = 0;
    LRESULT Return = 0;

    // Handle of application window.
    // Get it by using FindWindowEx function.
    // Here for compilation, i get the handle of my dialog.
    HWND hWnd = GetSafeHwnd();

    // Send the NULL message to the window.
    // SMTO_ABORTIFHUNG is specified to return immediately,
    // if the process is hung.
    Return = ::SendMessageTimeout( hWnd, // Window Handle
                               WM_NULL, // Message
                               0,       // WParam
                               0,       // LParam
                               SMTO_ABORTIFHUNG, // Flags
                               500,              // Timeout
                               &Result );        // Result

    // Check whether the WM_NULL message is processed.
    if( !Return )
    {
    // Since the WM_NULL message is not processed,
    // the targeted window is hung. Forget about it!
    }
    */
    DWORD Result = 0;
    LRESULT Return = 0;
    Return = ::SendMessageTimeout( hwnd, // Window Handle
                                   WM_SETTEXT, // Message
                                   0,       // WParam
                                   (LPARAM)w,       // LParam
                                   SMTO_ABORTIFHUNG, // Flags
                                   15000,              // Timeout
                                   &Result);        // Result

    if( !Return )
    {
        cout << "message is not processed, the targeted window is hung" << endl;
    }

    //SendMessageW(hwnd, WM_SETTEXT, (WPARAM)0, (LPARAM)w);
    return 0;

    for (unsigned i = 0; i < wcslen(w); i++)
    {
        __SendChar(hwnd, hkl, w[i], i);
        /*
        int a = iswalnum(w[i]);
        int b = iswalpha(w[i]);
        int c = iswascii(w[i]);
        int d = iswpunct(w[i]);
        int e = iswprint(w[i]);
        e = 0;

        cout << (wchar_t)w[i] << " (" << i << ") - " << "iswalnum(" << a << ") iswalpha(" << b << ") iswascii(" << c << ") iswpunct(" << d << ") iswprint(" << e << ")" << endl;
        */
    }
    __SendKey(hwnd, VK_BACK, 0x0e, 0x0);
    __SendKey(hwnd, VK_BACK, 0x0e, 0x0);
    __SendKey(hwnd, VK_BACK, 0x0e, 0x0);
    return 0;
}
