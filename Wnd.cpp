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
#include "Wnd.h"
#include "InputMouse.h"

/* Debug output Only */
// #include <iostream>
// using namespace std;

BOOL DLL_EXPORT wndActivateWindow(HWND hwnd, BOOL isRenew)
{
    if (hwnd == NULL)
        return FALSE;

    WINDOWPLACEMENT place;
    ZeroMemory(&place, sizeof(place));
    place.length = sizeof(WINDOWPLACEMENT);

    if (!GetWindowPlacement(hwnd, &place))
        return FALSE;

    if ((isRenew) || (place.showCmd == SW_MINIMIZE) || (place.showCmd == SW_OTHERZOOM))
    {
        PostMessage(hwnd, WM_SYSCOMMAND, (WPARAM)SC_RESTORE, (LPARAM)0);
        Sleep(15);
    }
    return RedrawWindow(hwnd, NULL, 0, 0U);
}

BOOL DLL_EXPORT wndWakeUpScreen(HWND hwnd)
{
    HWND rwnd = ((hwnd) ? hwnd : GetDesktopWindow());
    if (
        (!rwnd) ||
        (!RedrawWindow(rwnd, NULL, 0, 0U))
       )
        return FALSE;

    POINT p = { 100, 500 };
    mouseMoveAW(rwnd, &p);
    return TRUE;
}

BOOL DLL_EXPORT wndSleepScreen(void)
{
    return SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, MAKELPARAM(2,0));
}

HWND DLL_EXPORT wndChildElement(HWND hwnd, const LPWSTR wclass, const LPWSTR wname, int idx)
{
    HWND rwnd = NULL;

    if ((hwnd == NULL) || (wclass == NULL))
        return rwnd;

    do
    {
        int cnt = 0;

        if (idx == 0)
        {
            rwnd = hwnd;
            break;
        }
        do
        {
            rwnd = FindWindowExW(hwnd, rwnd, wclass, wname);
            if (rwnd != NULL)
                ++cnt;
        }
        while ((cnt < idx) && (rwnd != NULL));
    }
    while (0);

    if ((!rwnd) && (wname))
    {
        return wndChildElement(hwnd, wclass, NULL, idx);
    }

    return rwnd;
}

HWND DLL_EXPORT wndChildLastElement(HWND hwnd, LPWSTR wclass, const LPWSTR wname)
{
    HWND rwnd = NULL;

    if (wclass == NULL)
        return rwnd;

    do
    {
        HWND twnd = NULL;

        do
        {
            twnd = FindWindowExW(hwnd, rwnd, wclass, wname);
            if (twnd != NULL)
                rwnd = twnd;
        }
        while (twnd != NULL);
    }
    while (0);

    if ((!rwnd) && (wname))
    {
        return wndChildLastElement(hwnd, wclass, NULL);
    }

    return rwnd;
}

HWND DLL_EXPORT wndChildTreeElement(HWND hwnd, const LPWSTR wclass, const LPWSTR wname)
{
    HWND rwnd = NULL;

    do
    {
        rwnd = FindWindowExW(hwnd, rwnd, wclass, wname);
        if (rwnd != NULL)
            return rwnd;
    }
    while (rwnd != NULL);

    do
    {
        rwnd = FindWindowExW(hwnd, rwnd, wclass, NULL);
        if (rwnd != NULL)
        {
            HWND twnd = wndChildTreeElement(rwnd, wclass, wname);
            if (twnd != NULL)
                return twnd;
        }
    }
    while (rwnd != NULL);

    return NULL;
}
