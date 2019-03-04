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

#define _WIN32_WINNT 0x0501
#include "InputDirectX.h"
#include "InputKey.h"
#include "Wnd.h"
#include "wchar.h"

/* Debug output Only */
//#include <stdio.h>
//#include <string.h>

typedef union
{
    LPARAM lparam;
    struct
    {
        unsigned nRepeatCount : 16;
        unsigned nScanCode : 8;
        unsigned nExtended : 1;
        unsigned nReserved : 4;
        unsigned nContext : 1;
        unsigned nPrev : 1;
        unsigned nTrans : 1;
    } data;
} dataLparam;

typedef struct
{
    wchar_t w;
    UINT key, scan, shift, numl;
} kbLayout;

typedef struct
{
    UINT      layoutSize;
    kbLayout *layoutArray;
    HKL job, old;
} kbLang;

static kbLayout kbLayoutNuml = { .w = 0x0, .key = VK_NUMLOCK, .scan = DIK_NUMLOCK, .shift = 0x0, .numl = 0xff };
static kbLayout kbLayoutBack = { .w = 0x0, .key = VK_BACK, .scan = DIK_BACK, .shift = 0x0, .numl = 0x0 };
static kbLayout kbLayout_Empty[] =  { { .w = 0x0, .key = 0x0, .scan = 0x0, .shift = 0x0, .numl = 0x0 } };
static kbLayout kbLayout_RU_00000419[] =
{
#define __KB_LAYOT(A,B,C,D,E) { .w = static_cast<wchar_t>(A), .key = B, .scan = C, .shift = D, .numl = E },
#include "InputKB_00000419.h"
};
static kbLayout kbLayout_RU_00010419[] =
{
#define __KB_LAYOT(A,B,C,D,E) { .w = static_cast<wchar_t>(A), .key = B, .scan = C, .shift = D, .numl = E },
#include "InputKB_00010419.h"
};

static void __sleep(size_t seed)
{
    Sleep(
        static_cast<DWORD> ((rand() % (seed * 75) + 1) + 200)
    );
}

static size_t __randomTextBack(size_t seed)
{
    return static_cast<size_t> (rand() % seed + 1);
}

static void __keyNumlock(HWND hwnd, dataLparam *dl)
{
    ZeroMemory(dl, sizeof(dataLparam));
    dl->data.nScanCode = kbLayoutNuml.scan;
    dl->data.nRepeatCount = 1;
    dl->data.nExtended = 1;

    PostMessageW(hwnd, WM_KEYDOWN,
                 reinterpret_cast<WPARAM>(static_cast<UINT> (kbLayoutNuml.key)),
                 reinterpret_cast<LPARAM>(dl->lparam)
                );

    Sleep(10);
    dl->data.nPrev = dl->data.nTrans = 1;

    PostMessageW(hwnd, WM_KEYUP,
                 reinterpret_cast<WPARAM>(static_cast<UINT> (kbLayoutNuml.key)),
                 reinterpret_cast<LPARAM>(dl->lparam)
                );

    ZeroMemory(dl, sizeof(dataLparam));
}

static void __keyShift(HWND hwnd, dataLparam *dl, kbLayout *kbl, UINT state)
{
    ZeroMemory(dl, sizeof(dataLparam));
    dl->data.nRepeatCount = 1;

    if (state == (UINT)WM_KEYDOWN)
    {
        unsigned long rep = 0,
                      r = (rand() % 10 + 1);

        dl->data.nScanCode = kbl->shift;
        dl->data.nPrev = 0;
        do
        {
            PostMessageW(hwnd, WM_KEYDOWN,
                         reinterpret_cast<WPARAM>((UINT)VK_SHIFT),
                         reinterpret_cast<LPARAM>(dl->lparam)
                        );
            rep++;
            dl->data.nPrev = 1;
        }
        while (rep < r);
    }
    else if (state == (UINT)WM_KEYUP)
    {
        dl->data.nScanCode = kbl->shift;
        dl->data.nPrev = dl->data.nTrans = 1;

        PostMessageW(hwnd, WM_KEYUP,
                     reinterpret_cast<WPARAM>((UINT)VK_SHIFT),
                     reinterpret_cast<LPARAM>(dl->lparam)
                    );
    }
    ZeroMemory(dl, sizeof(dataLparam));
}

static void __sendKey(HWND hwnd, kbLayout *kbl, int s)
{
    dataLparam dl;

    if (kbl->shift)
    {
        __keyShift(hwnd, &dl, kbl, WM_KEYDOWN);
        Sleep(25);
    }
    else if (kbl->numl)
    {
        __keyNumlock(hwnd, &dl);
        Sleep(15);
    }

    ZeroMemory(&dl, sizeof(dataLparam));
    dl.data.nScanCode = kbl->scan;
    dl.data.nRepeatCount = 1;
    PostMessageW(hwnd, WM_KEYDOWN,
                 reinterpret_cast<WPARAM>(static_cast<UINT> (kbl->key)),
                 reinterpret_cast<LPARAM>(dl.lparam)
                );

    dl.data.nRepeatCount = 0;
    dl.data.nPrev = dl.data.nTrans = 1;

    Sleep(static_cast<DWORD> (rand() % 100 + 1));

    PostMessageW(hwnd, WM_KEYUP,
                 reinterpret_cast<WPARAM>(static_cast<UINT> (kbl->key)),
                 reinterpret_cast<LPARAM>(dl.lparam)
                );

    if (kbl->shift)
    {
        __keyShift(hwnd, &dl, kbl, WM_KEYUP);
    }
    else if (kbl->numl)
    {
        __keyNumlock(hwnd, &dl);
    }
    __sleep(s);
}

static void __sendChar(HWND hwnd, kbLang *lng, wchar_t w, UINT pos, int s)
{
    kbLayout kbl = {0U, 0U, 0U, 0U, 0U};
    kbl.w = w;

    if ((iswupper(w)) || (!pos))
    {
        do
        {
            if (!iswalpha(w))
                break;

            if (iswupper(w))
            {
                LPWSTR wo;
                wchar_t wc[] = { w, L'\0' };

                wo = CharLowerW(const_cast<LPWSTR> (wc));
                if (wo == NULL)
                    break;

                kbl.w = wo[0];
            }
            kbl.shift = 0x2a;
        }
        while (0);
    }

    do
    {
        if ((iswpunct(w)) || (iswdigit(w)))
        {
            volatile BOOL isFound = FALSE;
            #           pragma omp parallel for schedule(static) shared(isFound)
            for (unsigned i = 0; i < lng->layoutSize; i++)
            {
                if (isFound)
                    continue;
                if (lng->layoutArray[i].w == w)
                {
                    memcpy(&kbl, &lng->layoutArray[i], sizeof(kbLayout));
                    isFound = TRUE;
                }
            }
        }

        if ((kbl.key) && (kbl.scan))
            break;

        if (iswascii(w))
        {
            kbl.key = VkKeyScanExW(kbl.w, lng->job);
            kbl.scan = MapVirtualKeyW(kbl.key, 0U);
        }
        else if (iswalnum(w))
        {
            kbl.key = VK_OEM_PERIOD;
            kbl.scan = MapVirtualKeyW(VkKeyScanExW(kbl.w, lng->job), 0U);
        }

        if ((!kbl.key) || (!kbl.scan))
            return;
    }
    while (0);

    __sendKey(hwnd, &kbl, s);
}

static void __changeLanguage(HWND hwnd, const LPWSTR codepg, kbLang *lng)
{
    /* EN: 00000409 RU: 00010419 */
    HKL hkl = NULL;

    if (!lng->job)
    {
        hkl = lng->job = LoadKeyboardLayoutW(codepg, KLF_ACTIVATE);

        switch(wcstoul(codepg, NULL, 10))
        {
        case 419U:
        {
            lng->layoutSize = __NELE(kbLayout_RU_00000419);
            lng->layoutArray = kbLayout_RU_00000419;
            break;
        }
        case 10419U:
        {
            lng->layoutSize = __NELE(kbLayout_RU_00010419);
            lng->layoutArray = kbLayout_RU_00010419;
            break;
        }
        default:
        {
            lng->layoutSize = 0U;
            lng->layoutArray = kbLayout_Empty;
            break;
        }
        }
    }

    if (!lng->old)
    {
        hkl = lng->old = ActivateKeyboardLayout(lng->job, KLF_SETFORPROCESS);
    }
    else
    {
        (void) ActivateKeyboardLayout(lng->old, KLF_SETFORPROCESS);
        hkl = lng->old;
    }

    if (!hkl)
        return;

    //PostMessage(hwnd, 0x0050, 2, 0);
    PostMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, 0U, reinterpret_cast<LPARAM> (hkl));
    //PostMessage(hwnd, WM_INPUTLANGCHANGE, 0U, reinterpret_cast<LPARAM>(hkl));
}

void DLL_EXPORT keySendTextElement(HWND hwnd, const LPWSTR codepg, LPWSTR text, size_t sz, LPWSTR wclass, LPWSTR wname, int idx)
{
    keySendText(
        wndChildElement(hwnd, wclass, wname, idx),
        codepg,
        text,
        sz
    );
}

void DLL_EXPORT keySendText(HWND hwnd, const LPWSTR codepg, LPWSTR text, size_t sz)
{
    if ((hwnd == NULL) || (text == NULL) || (!sz))
        return;

    if (!wndActivateWindow(hwnd, FALSE))
        return;

#   if defined(__InputKB_00000419)
    LPWSTR code = ((codepg == NULL) ? (LPWSTR)L"00000419" : codepg);
#   elif defined(__InputKB_00010419)
    LPWSTR code = ((codepg == NULL) ? const_cast<LPWSTR> (L"00010419") : codepg);
#   else
    if (codepg == NULL)
        return;

    LPWSTR code = codepg;
#   endif

    wchar_t prev = L'\0';
    kbLang lng = { 0U, NULL, NULL, NULL };
    size_t r = __randomTextBack(sz);
    __changeLanguage(hwnd, code, &lng);

    if (lng.job == NULL)
        return;

    for (size_t i = 0U; i < sz; i++)
    {
        if (r == i)
        {
            r = __randomTextBack(sz - i);
            r += i;
            size_t pos = (
                             ((i % 5U) == 0) ?
                             ((i > 0U) ? (i - 1U) : (i + 1U)) :
                             ((i < (sz-1)) ? (i + 1U) : i)
                         );
            __sendChar(hwnd, &lng, text[pos], pos, 35);
            __sendKey(hwnd, &kbLayoutBack, 15);
        }
        __sendChar(hwnd, &lng, text[i], ((prev == L'.') ? 0U : i), 3);
        prev = (((prev == L'.') && (text[i] == L' ')) ? prev : text[i]);
    }
    __changeLanguage(hwnd, NULL, &lng);
}

BOOL DLL_EXPORT keySetText(HWND hwnd, const LPWSTR codepg, LPWSTR text)
{
    if ((hwnd == NULL) || (codepg == NULL) || (text == NULL))
        return FALSE;

    DWORD ret = 0L;
    LRESULT r = 0;
    kbLang lng = { 0U, NULL, NULL, NULL };
    __changeLanguage(hwnd, codepg, &lng);

    if (lng.job == NULL)
        return FALSE;

    r = SendMessageTimeout(hwnd,
                           WM_SETTEXT,
                           0,
                           reinterpret_cast<LPARAM> (text),
                           SMTO_ABORTIFHUNG,
                           3000,
                           &ret
                          );
    __changeLanguage(hwnd, NULL, &lng);
    return ((r) ? (!ret) : FALSE);
}
