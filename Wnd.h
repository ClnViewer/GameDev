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

#ifndef __WND_FIND_H__
#define __WND_FIND_H__

#if !defined(__CPP_CLIENT)
#include "loader.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*!
    Return handle window child element
    HWND - handle main window
    LPWSTR - class name, example for Notepad2 L"Scintilla", index 1
    int - index of element, if 0 return main window handle
*/
HWND DLL_EXPORT wndChildElement(HWND, const LPWSTR, const LPWSTR, int);
HWND DLL_EXPORT wndChildLastElement(HWND, const LPWSTR, const LPWSTR);
HWND DLL_EXPORT wndChildTreeElement(HWND, const LPWSTR, const LPWSTR);
BOOL DLL_EXPORT wndActivateWindow(HWND, BOOL);
BOOL DLL_EXPORT wndWakeUpScreen(HWND);
BOOL DLL_EXPORT wndSleepScreen(void);
void DLL_EXPORT wndScreenSaverOff(void);

/*!
    To C#

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
    public static extern IntPtr wndChildElement(IntPtr hwnd, string wclass, string wname, int idx);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
    public static extern IntPtr wndChildLastElement(IntPtr hwnd, string wclass, string wname);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
    public static extern IntPtr wndChildTreeElement(IntPtr hwnd, string wclass, string wname);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern bool wndActivateWindow(IntPtr hwnd, bool IsRenew);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern bool wndWakeUpScreen(IntPtr hwnd);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern bool wndSleepScreen();

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void wndScreenSaverOff();

*/

#ifdef __cplusplus
}
#endif

#endif
