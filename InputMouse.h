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

#ifndef __INPUT_MOUSE_H__
#define __INPUT_MOUSE_H__

#if !defined(__CPP_CLIENT)
#include "loader.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define __MOUSE_CORD(A,B) static_cast<int> (A + ((B / (rand() % 10 + 1)) / 2))

typedef enum
{
    M_LEFT_BTN,
    M_RIGHT_BTN,
    M_MIDLE_BTN
} mouse_click_e;

void DLL_EXPORT mouseLClickAW(HWND, POINT*, POINT*);
void DLL_EXPORT mouseRClickAW(HWND, POINT*, POINT*);
void DLL_EXPORT mouseMClickAW(HWND, POINT*, POINT*);
void DLL_EXPORT mouseMoveAW(HWND, POINT*);
void DLL_EXPORT mouseReInitAW(void);

void DLL_EXPORT mouseLClickBW(HWND, HWND, POINT*, POINT*);
void DLL_EXPORT mouseRClickBW(HWND, HWND, POINT*, POINT*);
void DLL_EXPORT mouseMClickBW(HWND, HWND, POINT*, POINT*);

/*!
    To C#

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void mouseLClickBW(IntPtr hwnd, IntPtr mwnd, ref CordPoint point, ref CordPoint rectele);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void mouseRClickBW(IntPtr hwnd, IntPtr mwnd, ref CordPoint point, ref CordPoint rectele);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void mouseMClickBW(IntPtr hwnd, IntPtr mwnd, ref CordPoint point, ref CordPoint rectele);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void mouseLClickAW(IntPtr hwnd, ref CordPoint point, ref CordPoint rectele);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void mouseRClickAW(IntPtr hwnd, ref CordPoint point, ref CordPoint rectele);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void mouseMClickAW(IntPtr hwnd, ref CordPoint point, ref CordPoint rectele);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void mouseMoveAW(IntPtr hwnd, ref CordPoint point);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void mouseReInitAW();

*/

#ifdef __cplusplus
}
#endif

#endif
