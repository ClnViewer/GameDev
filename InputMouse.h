#ifndef __INPUT_MOUSE_H__
#define __INPUT_MOUSE_H__

#include "loader.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define __MOUSE_CORD(A,B) (int)(A + ((B / (rand() % 10 + 1)) / 2))

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

    [StructLayout(LayoutKind.Sequential)]
    public struct CordPoint
    {
        public int x, y;
    }

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
    public static extern void keySendText(IntPtr hwnd, string text, uint sz);

    [DllImport("GameDev.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Auto)]
    public static extern void keySendTextElement(IntPtr hwnd, string text, uint sz, string wclass, string wname, int idx);


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
