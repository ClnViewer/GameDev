#ifndef __WND_FIND_H__
#define __WND_FIND_H__

#include "loader.h"

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
    public static extern bool wndWakeUpWindow(IntPtr hwnd);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern bool wndSleepScreen();
*/

#ifdef __cplusplus
}
#endif

#endif
