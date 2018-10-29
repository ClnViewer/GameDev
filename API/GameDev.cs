using ConsoleAnouncerTest;
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
