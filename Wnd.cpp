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
    return TRUE;
}

BOOL DLL_EXPORT wndWakeUpScreen(HWND hwnd)
{
    HWND rwnd = ((hwnd) ? hwnd : GetDesktopWindow());
    if (!rwnd)
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
