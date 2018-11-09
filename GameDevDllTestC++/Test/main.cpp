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

#include "..\\..\\loader.h"
#include "..\\..\\Wnd.h"
#include "..\\..\\InputKey.h"
#include "..\\..\\InputMouse.h"
#include "..\\..\\BitMap.h"

#include "..\\..\\API\\GameDevClass.hpp"


#include <iostream>
using namespace std;

void printInfo(HWND hwnd, const char *fun, int line)
{
    WCHAR wstrk[KL_NAMELENGTH];
    GetKeyboardLayoutNameW(wstrk);
    printf("KB code page ID: %ls\n", wstrk);

    char Buff[64] = {0};
    sprintf(Buff, "%p", hwnd);
    cout << "WinID [" << fun << "][" << line << "]: " << Buff << endl;
}

HWND testMouseToWindow()
{
    HWND hwnd = wndChildLastElement(NULL, (const LPWSTR)L"Qt5QWindowIcon", (const LPWSTR)L"MEmu");
    if (hwnd == NULL)
    {
        cout << "hwnd is NULL" << endl;
        return NULL;
    }
    if (!IsWindow(hwnd))
    {
        cout << "hwnd is IsWindow bad" << endl;
        return NULL;
    }
    printInfo(hwnd, __func__, __LINE__);

    HWND mwnd = wndChildTreeElement(hwnd, (const LPWSTR)L"Qt5QWindowIcon", (const LPWSTR)L"RenderWindowWindow");
    if (mwnd == NULL)
    {
        cout << "mwnd is NULL" << endl;
        return NULL;
    }
    if (!IsWindow(mwnd))
    {
        cout << "mwnd is IsWindow bad" << endl;
        return NULL;
    }
    printInfo(mwnd, __func__, __LINE__);

    // POINT clientPoint;
    // ClientToScreen(hwnd, &clientPoint);
    // cout << "Point screen: " << clientPoint.x << "/" << clientPoint.y << endl;

    Sleep(5000);
    POINT point = { .x = 10, .y = 300 };
    POINT ele = { .x = 25, .y = 35 };

    mouseLClickBW(hwnd, mwnd, &point, &ele);
    return hwnd;
}

HWND testKeyToWindow(wchar_t *str)
{
    HWND hwnd = wndChildLastElement(NULL, (const LPWSTR)L"Qt5QWindowIcon", (const LPWSTR)L"MEmu");
    if (hwnd == NULL)
    {
        cout << "hwnd is NULL" << endl;
        return NULL;
    }
    if (!IsWindow(hwnd))
    {
        cout << "hwnd is IsWindow bad" << endl;
        return NULL;
    }
    printInfo(hwnd, __func__, __LINE__);

    keySendText(
        hwnd,
        /*L"00000409", EN*/
        /*L"00000419", RU*/
        /*L"00010419", RU машинопись*/
        (const LPWSTR)L"00010419",
        str,
        wcslen(str)
    );

    printInfo(hwnd, __func__, __LINE__);
    return hwnd;
}

HWND testCaptureWindow()
{
    HWND hwnd;
    POINT wsize = { 1207, 690 };
    HBITMAP hbmp = hbmpGetWindow((const LPWSTR)L"Qt5QWindowIcon", (const LPWSTR)L"MEmu", true, &wsize, &hwnd);
    if (hwnd == NULL)
    {
        cout << "hwnd is NULL" << endl;
        return NULL;
    }
    if (hbmp == NULL)
    {
        cout << "hbmp is NULL" << endl;
        return NULL;
    }
    printInfo(hwnd, __func__, __LINE__);
    hbmpSave(hbmp, (const LPWSTR)L"capture.bmp");
    DeleteObject(hbmp);
    return hwnd;
}

HWND tezt(HWND hwnd, LPWSTR wclass, const LPWSTR wname)
{
    HWND fwnd = NULL;

    do
    {
        fwnd = FindWindowExW(hwnd, fwnd, wclass, wname);
        if (fwnd != NULL)
        {
            char Buff[64] = {0};
            sprintf(Buff, "%p", fwnd);
            cout << "WinID 0 [" << Buff << "]"  << endl;
            return fwnd;
        }
    }
    while (fwnd != NULL);

    do
    {
        fwnd = FindWindowExW(hwnd, fwnd, wclass, NULL);
        if (fwnd != NULL)
        {
            char Buff[64] = {0};
            sprintf(Buff, "%p", fwnd);
            cout << "WinID 1 [" << Buff << "]"  << endl;

            HWND twnd = tezt(fwnd, wclass, wname);
            if (twnd != NULL)
                return twnd;
        }
    }
    while (fwnd != NULL);

    return NULL;
}

typedef BOOL (*pGetDevicePowerState)(HANDLE, BOOL*);

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    /*
    unsigned char buf[1024 * 75] = {0};

    FILE *f = fopen( "C:\\__BuildSource\\__TEST__\\__COC__\\GameDevDll\\bin\\Debug\\test-psp-RGB-BTN.bmp", "rb" );
    if(!f)
    {
        cout << "FILE is null" << endl;
        return 1;
    }

    fread((void*)buf, 1, sizeof(buf), f);
    fclose(f);

    HBITMAP hbmp = hbmpFromBuffer(buf);
    */

    HBITMAP hbmp = hbmpFromFile((const LPWSTR)L"C:\\__BuildSource\\__TEST__\\__COC__\\GameDevDll\\bin\\Debug\\test-psp-RGB-BTN.bmp", NULL);
    if(!hbmp)
    {
        cout << "HBITMAP is null" << endl;
        return 1;
    }

    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, hbmp);
    CloseClipboard();

    hbmpSave(hbmp, (const LPWSTR)L"save-test.bmp");

    DeleteObject(hbmp);

    return 0;
}
