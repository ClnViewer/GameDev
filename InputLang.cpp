#define _WIN32_WINNT 0x0501
#include "InputKey.h"

static struct kbdLang __kbdLang[] = {
#    define __LNG_ID(A,B) { .key = (LPWSTR)L##A, .name = (LPWSTR)L##B },
#    include "InputLangID.h"
    { .key = NULL, .name = NULL }
};

struct kbdLang * DLL_EXPORT keyLangList(void)
{
    return __kbdLang;
}
