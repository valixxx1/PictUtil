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

#include "chsum.h"

void chsumtable(u32 *table)
{
  t32 n, k;
  u32 c;

  for (n = 0; n < 256; n++)
    {
      c = (u32) n;
      for (k = 0; k < 8; k++)
        {
          if (c & 1)
            c = 0xedb88320L ^ (c >> 1);
          else
            c = c >> 1;
        }
      table[n] = c;
    }
}

u32 checksum32(u32 *table, u8 *b, u64 len)
{
  u32 c = -1;
  u64 n;

  for (n = 0; n < len; n++)
    c = table[(c ^ b[n]) & 0xff] ^ (c >> 8);

  return c ^ -1;
}

u8* chunk_chsum_buf(struct chunk *chunk)
{
  u8 *buf;

  if (chunk->len)
    {
      buf = malloc(chunk->len + 4);
      memcpy(buf, chunk->type, 4);
      memcpy(buf + 4, chunk->data, chunk->len);
    }
  else
    {
      buf = malloc(4);
      memcpy(buf, chunk->type, 4);
    }

  return buf;
}

void chunk_chsum(struct chunk *chunk)
{
  u32 table[256];
  u8 *buf;

  chsumtable(table);

  buf = chunk_chsum_buf(chunk);
  chunk->check = checksum32(table, buf, chunk->len + 4);
  free(buf);
}
