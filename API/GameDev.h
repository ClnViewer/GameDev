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

#ifndef __GAME_DEV_H__
#define __GAME_DEV_H__

/* 
    Warning! Auto generate, do not edit!
 */

#define DLL_EXPORT __declspec(dllimport)

#ifdef __cplusplus
extern "C"
{
#endif

/* Header from file: BitMap.h */
double  DLL_EXPORT   bmpComparable(struct dataComparable*);
void    DLL_EXPORT   bmpGrayscale(BOOL, BYTE*, BYTE*, int, int, int);
HBITMAP DLL_EXPORT   hbmpFromBuffer(BYTE*, POINT*);
HBITMAP DLL_EXPORT   hbmpFromFile(const LPWSTR, POINT*);
HBITMAP DLL_EXPORT   hbmpGetWindow(const LPWSTR, const LPWSTR, BOOL, POINT*, HWND*);
HBITMAP DLL_EXPORT   hbmpCaptureWindow(HWND, POINT*);
BOOL    DLL_EXPORT   hbmpGrayscale(HBITMAP, BOOL);
BOOL    DLL_EXPORT   hbmpSave(HBITMAP, const LPWSTR);
void    DLL_EXPORT   hbmpFree(HBITMAP);


/* Header from file: InputKey.h */
struct kbdLang * DLL_EXPORT keyLangList(int*);
BOOL DLL_EXPORT keySetText(HWND, const LPWSTR, LPWSTR);
void DLL_EXPORT keySendText(HWND, const LPWSTR, LPWSTR, size_t);
void DLL_EXPORT keySendTextElement(HWND, const LPWSTR, LPWSTR, size_t, const LPWSTR, const LPWSTR, int);


/* Header from file: InputMouse.h */
void DLL_EXPORT mouseLClickAW(HWND, POINT*, POINT*);
void DLL_EXPORT mouseRClickAW(HWND, POINT*, POINT*);
void DLL_EXPORT mouseMClickAW(HWND, POINT*, POINT*);
void DLL_EXPORT mouseMoveAW(HWND, POINT*);
void DLL_EXPORT mouseReInitAW(void);
void DLL_EXPORT mouseLClickBW(HWND, HWND, POINT*, POINT*);
void DLL_EXPORT mouseRClickBW(HWND, HWND, POINT*, POINT*);
void DLL_EXPORT mouseMClickBW(HWND, HWND, POINT*, POINT*);


/* Header from file: Wnd.h */
HWND DLL_EXPORT wndChildElement(HWND, const LPWSTR, const LPWSTR, int);
HWND DLL_EXPORT wndChildLastElement(HWND, const LPWSTR, const LPWSTR);
HWND DLL_EXPORT wndChildTreeElement(HWND, const LPWSTR, const LPWSTR);
BOOL DLL_EXPORT wndActivateWindow(HWND, BOOL);
BOOL DLL_EXPORT wndWakeUpScreen(HWND);
BOOL DLL_EXPORT wndSleepScreen(void);
void DLL_EXPORT wndScreenSaverOff(void);


/* Header from file: version.h */


#ifdef __cplusplus
}
#endif

#endif
/*
	Last Changed Rev: 846
	Last Changed Date: 2019-02-06 05:35:31 +0400 (Wed, 06 Feb 2019)
 */


