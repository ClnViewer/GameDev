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
    [return: MarshalAs(UnmanagedType.R8)]
    public static extern double bmpComparable(ref ComparableData data);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void bmpGrayscale(bool m, IntPtr src, IntPtr dst, int x, int y, int t);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
    public static extern bool hbmpSave(IntPtr hbmp, string text);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl]
    public static extern void hbmpFree(IntPtr hbmp);

*/

#ifdef __cplusplus
}
#endif

#endif
