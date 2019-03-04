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

#include "..\loader.h"
#include "..\Wnd.h"
#include "..\InputKey.h"
#include "..\InputMouse.h"
#include "..\BitMap.h"

//#include "..\API\GameDevClass.hpp"

#include <iostream>
#include <string>

using namespace std;

void printInfo(HWND hwnd, const char *fun, int line)
{
    wchar_t wstrk[KL_NAMELENGTH] = {0};
    GetKeyboardLayoutNameW(wstrk);
    wcout << "KBCID: [" << wstrk << "]" << endl;
    wcout << "WinID: [" << fun << "][" << line << "]: " << static_cast<void*>(hwnd) << endl;
}

int main(int argc, char *argv[])
{
    const LPWSTR cwclass = (LPWSTR)&L"Qt5QWindowIcon";
    const LPWSTR cwemu = (LPWSTR)&L"MEmu";
    wstring fname(L"");

    if (argc > 1)
    {
        string s(argv[1]);
        fname.append(s.begin(), s.end());
    }
    else
        fname.append(L"capture.bmp");

    HWND hwnd;
    POINT wsize = { 1207, 690 };
    HBITMAP hbmp = hbmpGetWindow(cwclass, cwemu, true, &wsize, &hwnd);
    if (hwnd == NULL)
    {
        wcout << L"Not find running Application: " << cwemu << L", window: " << cwclass << endl;
        return 127;
    }
    if (hbmp == NULL)
    {
        wcout << L"Not capture window from Application: " << cwemu << L", window: " << cwclass << endl;
        return 127;
    }

    printInfo(hwnd, __func__, __LINE__);

    if (hbmpSave(hbmp, (LPWSTR)fname.c_str()))
        wcout << L"Save file as: " << fname << endl;
    else
        wcout << L"Save file " << fname << L" ERROR" << endl;

    DeleteObject(hbmp);
    return 0;
}
