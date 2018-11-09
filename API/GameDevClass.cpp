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

#if defined(__GAME_DEV_EXCEPT)
#   include <stdexcept>
#   define __EX_TRY try {
#   define __EX_CATCH } catch(exception& e) { throw e; }
#   define __EX_EXCEPT(A,B) throw A(B);
#else
#   define __EX_TRY
#   define __EX_CATCH
#   define __EX_EXCEPT(A,B) return;
#endif

#include "..\\loader.h"
#include "..\\Wnd.h"
#include "..\\BitMap.h"
#include "..\\InputKey.h"
#include "..\\InputMouse.h"

using namespace std;

#include "GameDevClass.hpp"

GameDev::GameDev (const LPWSTR wclass, const LPWSTR wname, const LPWSTR wmouse)
{
    __EX_TRY
        if (!wclass)
            __EX_EXCEPT(std::invalid_argument, "name window class empty");

        ZeroMemory(GameDev::codepage, sizeof(GameDev::codepage));
        if (!(GameDev::hwnd = wndChildLastElement(NULL, wclass, wname)))
            __EX_EXCEPT(std::logic_error, "active window not found");

        if ((wmouse) && (GameDev::hwnd))
        {
            if (!(GameDev::mwnd = wndChildTreeElement(GameDev::hwnd, wclass, wmouse)))
                __EX_EXCEPT(std::logic_error, "active mouse window not found");
        }
        else
            GameDev::mwnd = nullptr;
    __EX_CATCH
}
GameDev::~GameDev ()
{
    hbmpFree(GameDev::hbmp);
}
bool GameDev::IsMainWinHandle()
{
    if (!GameDev::hwnd)
        return false;
    return true;
}
bool GameDev::IsMouseWinHandle()
{
    if (!GameDev::mwnd)
        return false;
    return true;
}
bool GameDev::WakeUpScreen()
{
    return wndWakeUpScreen(GameDev::hwnd);
}
bool GameDev::SleepScreen()
{
    return wndSleepScreen();
}
void GameDev::ScreenSaverOff()
{
    wndScreenSaverOff();
}
bool GameDev::BmpFromFile(const LPWSTR fname)
{
    if (GameDev::hbmp)
        DeleteObject(GameDev::hbmp);

    GameDev::hbmp = hbmpFromFile(fname, &BmpSize);
    return ((!GameDev::hbmp) ? false : true);
}
bool GameDev::BmpFromByte(BYTE *barray)
{
    if (GameDev::hbmp)
        DeleteObject(GameDev::hbmp);

    GameDev::hbmp = hbmpFromBuffer(barray, &BmpSize);
    return ((!GameDev::hbmp) ? false : true);
}
bool GameDev::BmpGrayscale (bool isBW)
{
    bool ret;

    if (!GameDev::hbmp)
        return false;

    if (!(ret = hbmpGrayscale(GameDev::hbmp, isBW)))
    {
        DeleteObject(GameDev::hbmp);
        GameDev::hbmp = NULL;
    }
    return ret;
}
bool GameDev::BmpEquals (struct dataComparable *data)
{
    double r = bmpComparable(data);
    if (r < 98.0)
        return false;
    return true;
}
bool GameDev::BmpSave (const LPWSTR fname)
{
    if (!GameDev::hbmp)
        return false;
    return hbmpSave(GameDev::hbmp, fname);
}
bool GameDev::BmpCapture (POINT *point)
{
    if (
        (!GameDev::hwnd) ||
        (!IsWindow(GameDev::hwnd)) ||
        (!wndActivateWindow(GameDev::hwnd, false))
    )
        return false;

    if (GameDev::hbmp)
        hbmpFree(GameDev::hbmp);

    if (!(GameDev::hbmp = hbmpCaptureWindow(GameDev::hwnd, point)))
        return false;
    return true;
}
bool GameDev::MouseClickL (POINT *winr, POINT *eler)
{
    if (!GameDev::hwnd)
        return false;
    mouseLClickBW(GameDev::hwnd, GameDev::mwnd, winr, eler);
    return true;
}
bool GameDev::MouseClickR (POINT *winr, POINT *eler)
{
    if (!GameDev::hwnd)
        return false;
    mouseRClickBW(GameDev::hwnd, GameDev::mwnd, winr, eler);
    return true;
}
bool GameDev::MouseClickM (POINT *winr, POINT *eler)
{
    if (!GameDev::hwnd)
        return false;
    mouseMClickBW(GameDev::hwnd, GameDev::mwnd, winr, eler);
    return true;
}
bool GameDev::KbdText (const LPWSTR cpage, LPWSTR str, size_t sz)
{
    LPWSTR code = ((!cpage) ? GameDev::codepage : cpage);
    if (
        (!GameDev::hwnd) ||
        (!code)
    )
        return false;

    keySendText(GameDev::hwnd, code, str, sz);
    return true;
}
bool GameDev::KbdCodePage(const LPWSTR cpage)
{
    size_t sz;

    if (
        (!cpage) ||
        (!(sz = wcslen(cpage))) ||
        (!wcsncpy(GameDev::codepage, cpage, sz))
    )
        return false;
    return true;
}

