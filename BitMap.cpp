#define _WIN32_WINNT 0x0501
#include "BitMap.h"

double DLL_EXPORT bmpComparable(struct dataComparable *data)
{
    size_t i, sz, cmp = 0U;

    if (!data)
        return 0L;

    sz = ((data->d1.sz > data->d2.sz) ? data->d2.sz : data->d1.sz);

#   pragma omp parallel for private(i) schedule(dynamic) reduction(+:cmp)
    for (i = 0U; i < sz; i++)
    {
        if (data->d1.d[i] == data->d2.d[i])
            cmp++;
    }
    if (!cmp)
        return 0.0;
    if (cmp == sz)
        return 100.0;
    return ((double)cmp / ((double)sz / 100.0));
}

static bitPixel __PixelBlackWhite(bitPixel& pixel)
{
    // variant:
    // rgb = (int) (Math.Round (((double) (cR + cG + cB) / 3.0) / 255) * 255);
    //
    bitPixel p;
    p.Red = p.Green = p.Blue = (
             (
              ((unsigned)(0.299 * pixel.Red) > 126U) ||
              ((unsigned)(0.587 * pixel.Green) > 126U) ||
              ((unsigned)(0.114 * pixel.Blue) > 126U)
             ) ?
                static_cast<BYTE>(0xFF) : static_cast<BYTE>(0x0)
    );
    p.Alpha = static_cast<BYTE>(0x0);
    return p;
}

static bitPixel __PixelGrayscale(bitPixel& pixel)
{
    bitPixel p;
    p.Red = p.Green = p.Blue = static_cast<BYTE>(
            (0.299 * pixel.Red)
          + (0.587 * pixel.Green)
          + (0.114 * pixel.Blue)
    );
    p.Alpha = pixel.Alpha;
    return p;
}

void DLL_EXPORT bmpGrayscale(BOOL mode, BYTE *src, BYTE *dst, int w, int h, int t)
{
    if ((!src) || (!dst))
        return;

#   pragma omp parallel for schedule(dynamic)
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int off = x * sizeof(bitPixel) + y * t;
            {
                bitPixel& s = *reinterpret_cast<bitPixel*>(src + off);
                bitPixel& d = *reinterpret_cast<bitPixel*>(dst + off);
                d = ((mode) ?
                     __PixelBlackWhite(s) :
                     __PixelGrayscale(s)
                );
            }
        }
    }
}
