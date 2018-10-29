#ifndef __INPUT_KEY_H__
#define __INPUT_KEY_H__

#include "loader.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct kbdLang
{
    LPWSTR key;
    LPWSTR name;
};

struct kbdLang * DLL_EXPORT keyLangList(void);
BOOL DLL_EXPORT keySetText(HWND, const LPWSTR, LPWSTR);
void DLL_EXPORT keySendText(HWND, const LPWSTR, LPWSTR, size_t);
void DLL_EXPORT keySendTextElement(HWND, const LPWSTR, LPWSTR, size_t, const LPWSTR, const LPWSTR, int);

/*!
    To C#

    [StructLayout(LayoutKind.Sequential)]
    public struct CordPoint
    {
        public int x, y;
    }
    [StructLayout(LayoutKind.Sequential)]
    public struct KbdLang
    {
        string key;
        string name;
    }

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
    public static extern void keySendText(IntPtr hwnd, string text, uint sz);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
    public static extern void keySendTextElement(IntPtr hwnd, string text, uint sz, string wclass, string wname, int idx);

*/

#ifdef __cplusplus
}
#endif

#endif
