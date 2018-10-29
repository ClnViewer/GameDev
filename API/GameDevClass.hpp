#define _WIN32_WINNT 0x0501
#include <windows.h>

class DLL_EXPORT GameDev
{
private:
    HBITMAP hbmp;
    HWND    hwnd;
    HWND    mwnd;
    wchar_t codepage[10];

public:
    GameDev(const LPWSTR wclass, const LPWSTR wname, const LPWSTR wmouse);
    ~GameDev();
    bool IsMainWinHandle();
    bool IsMouseWinHandle();
    bool WakeUpScreen();
    bool SleepScreen();
    /* Bitmap */
    bool BmpCapture (POINT *point);
    bool BmpGrayscale (bool isBW);
    bool BmpEquals (struct dataComparable *data);
    bool BmpSave (const LPWSTR);
    /* Keyboard : Background work */
    bool KbdCodePage(const LPWSTR codepage);
    bool KbdText (const LPWSTR codepage, LPWSTR str, size_t sz);
    /* Mouse : Background work */
    bool MouseClickL (POINT *winr, POINT *eler);
    bool MouseClickR (POINT *winr, POINT *eler);
    bool MouseClickM (POINT *winr, POINT *eler);
};
