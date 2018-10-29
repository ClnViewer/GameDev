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

static long btnDown[] =
{
    WM_LBUTTONDOWN, WM_RBUTTONDOWN, WM_MBUTTONDOWN
};
static long btnUp[] =
{
    WM_LBUTTONUP, WM_RBUTTONUP, WM_MBUTTONUP
};

static void __mouseClickAction(HWND hwnd, HWND mwnd, POINT *p, POINT *e, mouse_click_e eclick)
{
    if ((hwnd == NULL) || (mwnd == NULL) || (p == NULL) || (e == NULL))
        return;

    if (
        (!IsWindow(hwnd)) ||
        (!IsWindow(mwnd))
    )
        return;

    long x = __MOUSE_CORD(p->x, e->x),
         y = __MOUSE_CORD(p->y, e->y),
         px = (int)(x / 10),
         py = (int)(y / 10),
         i = 1;

    /*
        // Debug offset:

        printf("\t\t\tI API %s:%d -> [%ld:%ld](x/y)\n", __func__, __LINE__, e->x, e->y);
        printf("\t\t\tT API %s:%d -> [%ld:%ld][%ld:%ld]\n", __func__, __LINE__, x, y, px, py);
        printf("\t\t\tM API %s:%d -> [%ld:%ld](max)\n", __func__, __LINE__, (p->x + e->x), (p->y + e->y));
        printf("\t\t\tM API %s:%d -> [%ld:%ld](min)\n", __func__, __LINE__, p->x, p->y);
        printf("\t\t\tM API %s:%d -> [%ld:%ld](rand)\n", __func__, __LINE__, (long)__MOUSE_CORD(p->x, e->x), (long)__MOUSE_CORD(p->y, e->y));
    */

    PostMessage(mwnd,
                WM_SETFOCUS,
                0x0,
                0x0
               );

    do
    {
        PostMessage(mwnd,
                    WM_MOUSEMOVE,
                    0x0,
                    MAKELPARAM(
                        ((px * i) + (rand() % 10)),
                        ((py * i) + (rand() % 10))
                    )
                   );
    }
    while (++i <= 10);

    PostMessage(mwnd,
                WM_MOUSEMOVE,
                0x0,
                MAKELPARAM(
                    x,
                    y
                )
               );
    /*
    PostMessage(mwnd,
                WM_MOUSEACTIVATE,
                (WPARAM)hwnd,
                MAKELPARAM(
                    1,
                    btnDown[eclick]
                )
               );
    */
    PostMessage(mwnd,
                btnDown[eclick],
                0x00000001,
                MAKELPARAM(
                    x,
                    y
                )
               );
    PostMessage(mwnd,
                btnUp[eclick],
                0x00000000,
                MAKELPARAM(
                    x,
                    y
                )
               );
    /*
    PostMessage(mwnd,
                WM_KILLFOCUS,
                0x0,
                0x0
               );
    */
}

void DLL_EXPORT mouseLClickBW(HWND hwnd, HWND mwnd, POINT *p, POINT *e)
{
    __mouseClickAction(hwnd, mwnd, p, e, M_LEFT_BTN);
}

void DLL_EXPORT mouseRClickBW(HWND hwnd, HWND mwnd, POINT *p, POINT *e)
{
    __mouseClickAction(hwnd, mwnd, p, e, M_RIGHT_BTN);
}

void DLL_EXPORT mouseMClickBW(HWND hwnd, HWND mwnd, POINT *p, POINT *e)
{
    __mouseClickAction(hwnd, mwnd, p, e, M_MIDLE_BTN);
}

