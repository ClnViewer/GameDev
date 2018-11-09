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

#ifndef __BIT_MAP_H__
#define __BIT_MAP_H__

#include "loader.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct bitPixel {
  BYTE Blue;
  BYTE Green;
  BYTE Red;
  BYTE Alpha;
};

struct dataItem
{
    BYTE *d;
    size_t sz;
};

struct dataComparable
{
    struct dataItem d1, d2;
};

/*! Bitmap RAW data */
double  DLL_EXPORT   bmpComparable(struct dataComparable*);
void    DLL_EXPORT   bmpGrayscale(BOOL, BYTE*, BYTE*, int, int, int);

/*! Bitmap HBITMAP data */
HBITMAP DLL_EXPORT   hbmpFromBuffer(BYTE*, POINT*);
HBITMAP DLL_EXPORT   hbmpFromFile(const LPWSTR, POINT*);
HBITMAP DLL_EXPORT   hbmpGetWindow(const LPWSTR, const LPWSTR, BOOL, POINT*, HWND*);
HBITMAP DLL_EXPORT   hbmpCaptureWindow(HWND, POINT*);
BOOL    DLL_EXPORT   hbmpGrayscale(HBITMAP, BOOL);
BOOL    DLL_EXPORT   hbmpSave(HBITMAP, const LPWSTR);
void    DLL_EXPORT   hbmpFree(HBITMAP);

/*!
    To C#

     [StructLayout(LayoutKind.Sequential)]
     public struct ComparableDataItem
     {
         public IntPtr d;
         public UInt32 sz;
     };
     [StructLayout(LayoutKind.Sequential)]
     public struct ComparableData
     {
         public ComparableDataItem d1, d2;
     }

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr hbmpCaptureWindow(IntPtr hwnd, ref CordPoint winsize);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
    public static extern IntPtr hbmpGetWindow(string wclass, string wname, bool isBW, ref CordPoint winsize, out IntPtr hwnd);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern bool hbmpGrayscale(IntPtr hbmp, bool isBW);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
    public static extern bool hbmpSave(IntPtr hbmp, string fname);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void hbmpFree(IntPtr hbmp);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    [return: MarshalAs(UnmanagedType.R8)]
    public static extern double bmpComparable(ref ComparableData data);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void bmpGrayscale(bool m, IntPtr src, IntPtr dst, int x, int y, int t);

*/

#ifdef __cplusplus
}
#endif

#endif
