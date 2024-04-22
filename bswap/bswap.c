/*  MIT License
 *
 *  Copyright (c) 2024 valixxx1
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include "bswap.h"

void bswap(void *x, u64 s)
{
  char *p = x;
  size_t lo, hi;
  for(lo=0, hi=s-1; hi>lo; lo++, hi--) {
    char tmp=p[lo];
    p[lo] = p[hi];
    p[hi] = tmp;
  }
}

/*
struct ihdr
{
  u32 len;
  t8 type[4];
  u32 width;
  u32 height;
  u8 bd;
  u8 cm;
  u8 zp;
  u8 fm;
  u8 im;
  u32 ch;
};
*/

void bswap_ihdr(struct ihdr *ihdr)
{
  bswap(&ihdr->len, 4);
  bswap(&ihdr->type, 4);
  bswap(&ihdr->height, 4);
  bswap(&ihdr->width, 4);
  bswap(&ihdr->bd, 1);
  bswap(&ihdr->cm, 1);
  bswap(&ihdr->zp, 1);
  bswap(&ihdr->fm, 1);
  bswap(&ihdr->im, 1);
  bswap(&ihdr->ch, 4);
}
