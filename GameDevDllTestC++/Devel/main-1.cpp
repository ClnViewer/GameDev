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

int main()
{
    wchar_t wwww[] = L"abc.,+-123Петр чайка";
    wchar_t www[] = L"18 is not 22 or yes!";
    wchar_t ww[] = L"ух 1234567890 летять утки, и 22 гуся (!\"№;%:?*()_+=-)";
    wchar_t w[] = L"ух 1234567890 летять утки, и 22 гуся. шли-бы они лесом! :)";

    bool ret1, ret2, check = TRUE;
    HWND hwnd = NULL;

    hwnd = GetDesktopWindow();
    if (hwnd == NULL)
    {
        cout << "hwnd is NULL" << endl;
        return 0;
    }

    //Sleep(2000);
    //SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_SCREENSAVE, (LPARAM)0);
    //Sleep(5000);
    cout << "SC_MONITORPOWER 2" << endl;
    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, MAKELPARAM(2,0));
    Sleep(5000);
    POINT p = { 100, 500 };
    mouseMoveAW(hwnd, &p);
    //SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 1);
    //Sleep(5000);
    /*
    cout << "SC_MONITORPOWER -1" << endl;
    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, MAKELPARAM(-1,0));
    Sleep(5000);
    cout << "SC_MONITORPOWER 1" << endl;
    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, MAKELPARAM(1,0));
    */
    return 0;

    while (check)
    {
        if (!SystemParametersInfo(SPI_GETSCREENSAVERRUNNING, 0, &ret1, 0))
        {
            cout << "SystemParametersInfo error" << endl;
            return 0;
        }
        if (!SystemParametersInfo(SPI_GETSCREENSAVEACTIVE, 0, &ret2, 0))
        {
            cout << "SystemParametersInfo error" << endl;
            return 0;
        }
        if ((ret1) || (ret2))
        {
            check = FALSE;
            cout << "ScreenSaver ON" << endl;
        }
        else
            cout << "ScreenSaver OFF" << endl;

        Sleep(1000);
    }

    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)-1);
    //Sleep(1000);
    //SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)1);
    return 0;

    //if (!(hwnd = testCaptureWindow())) return 127;
    if (!(hwnd = testMouseToWindow()))
        return 126;
    //if (!(hwnd = testKeyToWindow(w))) return 125;


    /*
        GameDev *gmdev = new GameDev((const LPWSTR)L"Notepad2", (const LPWSTR)L"Untiled - Notepad2");
        ret = gmdev->IsHandle();
        cout << "IsHandle return: " << ret << endl;
        ret = gmdev->BmpCapture(nullptr);
        cout << "Capture return: " << ret << endl;
        ret = gmdev->BmpSave((const LPWSTR)L"Cap-Notepad2.bmp");
        cout << "Save return: " << ret << endl;

        delete  gmdev;
    */

    /*
    WINDOWPLACEMENT place;
    ZeroMemory(&place, sizeof(place));
    place.length = sizeof(WINDOWPLACEMENT);
    GetWindowPlacement(hwnd, &place);
    printf("showCmd: %d\n", place.showCmd);

    if ((place.showCmd == SW_MINIMIZE) || (place.showCmd == SW_OTHERZOOM))
    {
        PostMessage(hwnd, WM_SYSCOMMAND, (WPARAM)SC_RESTORE, (LPARAM)0);
        printf("SW_MINIMIZE\n");
    }
    */
    //printf("wndActivateWindow: %d\n", wndActivateWindow(hwnd));

    /*
    hwnd = wndChildLastElement(NULL, (const LPWSTR)L"Qt5QWindowIcon", (const LPWSTR)L"MEmu");
    if (hwnd == NULL)
    {
        cout << "hwnd is NULL" << endl;
        return 0;
    }
    if (!IsWindow(hwnd))
    {
        cout << "hwnd is IsWindow bad" << endl;
        return 0;
    }
    HWND twnd = tezt(hwnd, (const LPWSTR)L"Qt5QWindowIcon", (const LPWSTR)L"RenderWindowWindow");
    if (twnd == NULL)
    {
        cout << "twnd is NULL" << endl;
        return 0;
    }
    */

    /*
    "MainWindowWindow"
      "CenterWidgetWindow"
        "RenderWindowWindow", Qt5QWindowIcon


    HWND mwnd = NULL, cwnd = NULL, rwnd = NULL;
    if ((hwnd = FindWindowExW(NULL, hwnd, L"Qt5QWindowIcon", L"MEmu")) != NULL)
    {
        printf("hwnd WINDOW FOUND\n");
        if ((mwnd = FindWindowExW(hwnd, mwnd, L"Qt5QWindowIcon", L"MainWindowWindow")) != NULL)
        {
            printf("mwnd WINDOW FOUND\n");
            if ((cwnd = FindWindowExW(mwnd, cwnd, L"Qt5QWindowIcon", L"CenterWidgetWindow")) != NULL)
            {
                printf("cwnd WINDOW FOUND\n");
                if ((rwnd = FindWindowExW(cwnd, rwnd, L"Qt5QWindowIcon", L"RenderWindowWindow")) != NULL)
                {
                    printf("rwnd WINDOW FOUND\n");
                }
                else
                {
                    return 0;
                }
            }
        }
    }
    */

    return 0;

    Sleep(7000);

    HWND mwnd = (HWND)0x00010304;
    char rBuff[64] = {0};
    sprintf(rBuff, "%p", mwnd);
    cout << "WinID 0 [" << rBuff << "]"  << endl;

    PostMessage(mwnd, WM_SETFOCUS, 0x0, 0x0);
    //Sleep(50);
    PostMessage(mwnd, WM_MOUSEMOVE, 0x0, MAKELPARAM(10,300));
    PostMessage(mwnd, WM_MOUSEMOVE, 0x0, MAKELPARAM(10,300));
    //Sleep(10);
    //PostMessage(mwnd, WM_MOUSEACTIVATE, (WPARAM)(HWND)0x000102C0, MAKELPARAM(1,WM_LBUTTONDOWN));
    //Sleep(10);
    PostMessage(mwnd, WM_LBUTTONDOWN, 0x00000001, MAKELPARAM(10,300));
    //Sleep(20);
    PostMessage(mwnd, WM_LBUTTONUP, 0x00000000, MAKELPARAM(10,300));
    PostMessage(mwnd, WM_KILLFOCUS, 0x0, 0x0);
    printf("SendMessage click!\n");

    return 0;
}
