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

﻿using ConsoleAnouncerTest;
using System;
using System.Runtime.InteropServices;

namespace GameDev
{
    public class API
    {
        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.R8)]
        public static extern double bmpComparable(ref Data.ComparableData data);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        public static extern IntPtr hbmpGetWindow(string wclass, string wname, bool isBW, ref Data.CordPoint point, out IntPtr hwnd);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
        public static extern void keySendText(IntPtr hwnd, string codepg, string text, uint sz);

        [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void mouseLClick(IntPtr hwnd, ref Data.CordPoint wpoint, ref Data.CordPoint epoint);

        [DllImport("gdi32.dll")]
        public static extern int DeleteObject(IntPtr obj);
    }
}
