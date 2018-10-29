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
#include "InputMouse.h"
#include "Wnd.h"
#include "wchar.h"

/* Debug output Only */
//#include <stdio.h>
//#include <string.h>

static double XSCALEFACTOR = 0.0;
static double YSCALEFACTOR = 0.0;

static long btnDown[] =
{
    MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_RIGHTDOWN, MOUSEEVENTF_MIDDLEDOWN
};
static long btnUp[] =
{
    MOUSEEVENTF_LEFTUP, MOUSEEVENTF_RIGHTUP, MOUSEEVENTF_MIDDLEUP
};

static void __mouse_ctors_init(void)
{
    XSCALEFACTOR = (0xffff / (GetSystemMetrics(SM_CXSCREEN) - 1));
    YSCALEFACTOR = (0xffff / (GetSystemMetrics(SM_CYSCREEN) - 1));
}
#if defined(__GNUC__)
static void __mouse_ctors_init(void) __attribute__ ((constructor));
#else
void (*initconfvar)(void) ELF_SECTION_ATR(".ctors") = __mouse_ctors_init;
#endif

static void __mouseMove(INPUT *mi, int x, int y)
{
    mi->mi.dx = (x * XSCALEFACTOR);
    mi->mi.dy = (y * YSCALEFACTOR);
    mi->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);
    //mi->mi.dwFlags = (MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE);

    SendInput(1, mi, sizeof(INPUT));
}

static void __mouseClick(INPUT *mi, mouse_click_e eclick)
{
    mi->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | btnDown[eclick]);
    SendInput(1, mi, sizeof(INPUT));

    Sleep(10);

    mi->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | btnUp[eclick]);
    SendInput(1, mi, sizeof(INPUT));
}

static HWND __mouseSetup(HWND hwnd, INPUT *mi, RECT *rect)
{
    if (hwnd == NULL)
        return NULL;

    if (
        (!IsWindow(hwnd)) ||
        (!wndActivateWindow(hwnd, FALSE))
    )
        return NULL;

    HWND chwnd;
    mi->type = INPUT_MOUSE;

    chwnd = GetForegroundWindow();
    SetForegroundWindow(hwnd);
    GetWindowRect(hwnd, rect);

return chwnd;
}

static void __mouseClickAction(HWND hwnd, POINT *p, POINT *e, mouse_click_e eclick)
{
    HWND  chwnd;
    RECT  rect = { 0, 0, 0, 0 };
    INPUT mi;
    ZeroMemory(&mi, sizeof(mi));

    if (!(chwnd = __mouseSetup(hwnd, &mi, &rect)))
        return;

    __mouseMove(&mi,
                (int)(rect.left + __MOUSE_CORD(p->x, e->x)),
                (int)(rect.top + __MOUSE_CORD(p->y, e->y))
               );
    __mouseClick(&mi, eclick);
    Sleep(150);
    SetForegroundWindow(chwnd);
}

static void __mouseMoveAction(HWND hwnd, POINT *p)
{
    HWND  chwnd;
    RECT  rect = { 0, 0, 0, 0 };
    INPUT mi;
    ZeroMemory(&mi, sizeof(mi));

    if (!(chwnd = __mouseSetup(hwnd, &mi, &rect)))
        return;

    __mouseMove(&mi,
                rect.left + p->x + ((rand() % 10) + 1),
                rect.top + p->y + ((rand() % 10) + 1)
               );
    Sleep(150);
    SetForegroundWindow(chwnd);
}

void DLL_EXPORT mouseLClickAW(HWND hwnd, POINT *p, POINT *e)
{
    __mouseClickAction(hwnd, p, e, M_LEFT_BTN);
}

void DLL_EXPORT mouseRClickAW(HWND hwnd, POINT *p, POINT *e)
{
    __mouseClickAction(hwnd, p, e, M_RIGHT_BTN);
}

void DLL_EXPORT mouseMClickAW(HWND hwnd, POINT *p, POINT *e)
{
    __mouseClickAction(hwnd, p, e, M_MIDLE_BTN);
}

void DLL_EXPORT mouseMoveAW(HWND hwnd, POINT *p)
{
    __mouseMoveAction(hwnd, p);
}

void DLL_EXPORT mouseReInitAW(void)
{
    if ((XSCALEFACTOR == 0.0) || (YSCALEFACTOR == 0.0))
        __mouse_ctors_init();
}
