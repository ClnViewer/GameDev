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

class DLL_EXPORT GameDev
{
private:
    HBITMAP hbmp;
    HWND    hwnd;
    HWND    mwnd;
    wchar_t codepage[10];

public:
    GameDev(const LPWSTR wclass, const LPWSTR wname, const LPWSTR wmouse);
    ~GameDev();
    bool IsMainWinHandle();
    bool IsMouseWinHandle();
    bool WakeUpScreen();
    bool SleepScreen();
    /* Bitmap */
    bool BmpCapture (POINT *point);
    bool BmpGrayscale (bool isBW);
    bool BmpEquals (struct dataComparable *data);
    bool BmpSave (const LPWSTR);
    /* Keyboard : Background work */
    bool KbdCodePage(const LPWSTR codepage);
    bool KbdText (const LPWSTR codepage, LPWSTR str, size_t sz);
    /* Mouse : Background work */
    bool MouseClickL (POINT *winr, POINT *eler);
    bool MouseClickR (POINT *winr, POINT *eler);
    bool MouseClickM (POINT *winr, POINT *eler);
};
