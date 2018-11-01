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

using System;
using System.Runtime.InteropServices;

namespace $rootnamespace$
{
    public class Data
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct CordPoint
        {
            public int x, y;
        }
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
        [StructLayout(LayoutKind.Sequential)]
        public struct KbdLang
        {
            string key;
            string name;
        }
    }
    public class API
    {
        /* Bitmap & HBitmap */

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.R8)]
        public static extern double bmpComparable(ref Data.ComparableData data);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void bmpGrayscale(bool m, IntPtr src, IntPtr dst, int x, int y, int t);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        public static extern IntPtr hbmpGetWindow(string wclass, string wname, bool isBW, ref Data.CordPoint point, out IntPtr hwnd);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool hbmpGrayscale(IntPtr hbmp, bool isBW);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        public static extern bool hbmpSave(IntPtr hbmp, string fname);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void hbmpFree(IntPtr hbmp);

        /* KeyBoard */

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        public static extern bool keySetText(IntPtr hwnd, string codepg, string text);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        public static extern void keySendText(IntPtr hwnd, string codepg, string text, uint sz);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        public static extern void keySendTextElement(IntPtr hwnd, string codepg, string text, uint sz, string wclass, string wname, int idx);

        /* Mouse */       

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void mouseLClickBW(IntPtr hwnd, IntPtr mwnd, ref Data.CordPoint point, ref Data.CordPoint rectele);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void mouseRClickBW(IntPtr hwnd, IntPtr mwnd, ref Data.CordPoint point, ref Data.CordPoint rectele);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void mouseMClickBW(IntPtr hwnd, IntPtr mwnd, ref Data.CordPoint point, ref Data.CordPoint rectele);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void mouseLClickAW(IntPtr hwnd, ref Data.CordPoint point, ref Data.CordPoint rectele);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void mouseRClickAW(IntPtr hwnd, ref Data.CordPoint point, ref Data.CordPoint rectele);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void mouseMClickAW(IntPtr hwnd, ref Data.CordPoint point, ref Data.CordPoint rectele);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void mouseMoveAW(IntPtr hwnd, ref Data.CordPoint point);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void mouseReInitAW();

        /* Wnd */

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

        /* WINAPI */

        [DllImport("gdi32.dll")]
        public static extern int DeleteObject(IntPtr obj);
    }
}
