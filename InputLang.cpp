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
#include "InputKey.h"

static struct kbdLang __kbdLang[] = {
#    define __LNG_ID(A,B) { .key = const_cast<LPWSTR>(L##A), .name = const_cast<LPWSTR>(L##B) },
#    include "InputLangID.h"
    { .key = NULL, .name = NULL }
};

struct kbdLang * DLL_EXPORT keyLangList(int *idx)
{
    if (idx)
    {
        *idx = __NELE(__kbdLang);
    }
    return __kbdLang;
}
