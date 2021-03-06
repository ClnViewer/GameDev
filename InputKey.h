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

#ifndef __INPUT_KEY_H__
#define __INPUT_KEY_H__

#if !defined(__CPP_CLIENT)
#include "loader.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

struct kbdLang
{
    LPWSTR key;
    LPWSTR name;
};
typedef struct kbdLang kbdLang;

struct kbdLang DLL_EXPORT * keyLangList(int*);
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
    public static extern bool keySetText(IntPtr hwnd, string codepg, string text);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
    public static extern void keySendText(IntPtr hwnd, string text, uint sz);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
    public static extern void keySendTextElement(IntPtr hwnd, string codepg, string text, uint sz, string wclass, string wname, int idx);

*/

#ifdef __cplusplus
}
#endif

#endif
