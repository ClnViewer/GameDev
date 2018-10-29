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

