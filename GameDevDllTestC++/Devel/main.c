
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "..\\BitMap.h"

void screenshot_window(HWND handle)
{
    RECT client_rect = { 0 };
    GetClientRect(handle, &client_rect);
    int width = client_rect.right - client_rect.left;
    int height = client_rect.bottom - client_rect.top;


    HDC hdcScreen = GetDC(handle);
    HDC hdc = CreateCompatibleDC(hdcScreen);
    HBITMAP hbmp = CreateCompatibleBitmap(hdcScreen, width, height);
    SelectObject(hdc, hbmp);

    BitBlt(hdc, 0, 0, width, height, hdcScreen, 0, 0, SRCCOPY);

    BITMAPINFO bmp_info = { 0 };
    bmp_info.bmiHeader.biSize = sizeof(bmp_info.bmiHeader);
    bmp_info.bmiHeader.biWidth = width;
    bmp_info.bmiHeader.biHeight = height;
    bmp_info.bmiHeader.biPlanes = 1;
    bmp_info.bmiHeader.biBitCount = 24;
    bmp_info.bmiHeader.biCompression = BI_RGB;

    int bmp_padding = (width * 3) % 4;
    if (bmp_padding != 0) bmp_padding = 4 - bmp_padding;

    BYTE *bmp_pixels = new BYTE[(width * 3 + bmp_padding) * height];;
    GetDIBits(hdc, hbmp, 0, height, bmp_pixels, &bmp_info, DIB_RGB_COLORS);

    BITMAPFILEHEADER bmfHeader;
    HANDLE bmp_file_handle = CreateFile("TestFile.bmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    // Add the size of the headers to the size of the bitmap to get the total file size
    DWORD dwSizeofDIB = (width * 3 + bmp_padding) * height + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    //Offset to where the actual bitmap bits start.
    bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

    //Size of the file
    bmfHeader.bfSize = dwSizeofDIB;

    //bfType must always be BM for Bitmaps
    bmfHeader.bfType = 0x4D42; //BM

    DWORD dwBytesWritten = 0;
    WriteFile(bmp_file_handle, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
    WriteFile(bmp_file_handle, (LPSTR)&bmp_info.bmiHeader, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
    WriteFile(bmp_file_handle, (LPSTR)bmp_pixels, (width * 3 + bmp_padding) * height, &dwBytesWritten, NULL);

    //Close the handle for the file that was created
    CloseHandle(bmp_file_handle);

    DeleteDC(hdc);
    DeleteObject(hbmp);
    ReleaseDC(NULL, hdcScreen);
    delete[] bmp_pixels;
}

int main()
{
    return 0;
}

int __main()
{
    //bmpTestLS("bin\\Debug\\main-screen-test.bmp");

    FILE *fp1 = fopen("bin\\Debug\\run-__STAGE_CHAT_CLOSE-0-0.bmp", "r"),
          *fp2 = fopen("bin\\Debug\\run-__STAGE_CHAT_CLOSE-1-1.bmp", "r");

    if ((!fp1))
    {
        printf("F1 error [%s]\n", strerror(errno));
        return 0;
    }
    if ((!fp2))
    {
        printf("F2 error [%s]\n", strerror(errno));
        return 0;
    }


    struct stat st1 = {0}, st2 = {0};

    fstat(fileno(fp1), &st1);
    fstat(fileno(fp2), &st2);

    printf("\n\tsize F1=%ld\n\tsize F2=%ld\n", st1.st_size, st2.st_size);

    struct dataComparable data = {0};

    data.d1.sz = st1.st_size;
    data.d2.sz = st2.st_size;

    data.d1.d = malloc(data.d1.sz);
    data.d2.d = malloc(data.d2.sz);

    fread(data.d1.d, 1, data.d1.sz,fp1);
    fread(data.d2.d, 1, data.d2.sz,fp2);

    double ret = bmpComparable(&data);
    printf("\n\tRETURN=%f\n", ret);

    fclose(fp1);
    fclose(fp2);
    return 0;
}
