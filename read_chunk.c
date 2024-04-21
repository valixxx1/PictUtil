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

#include "read_chunk.h"
#include "types.h"
#include "chunk.h"

static u32 read_u32(fl *f)
{
  u32 res;
  if (fread(&res, 4, 1, f) != 1) {
    exit(76);
  }
  return res;
}

void
read_chunk(fl *f, struct chunk *chunk)
{
  union word32 w;
  fill_word32(w);
  chunk->len = w.word;

  fill_word32(w);
  chunk->type[0] = w.bytes.b1;
  chunk->type[1] = w.bytes.b2;
  chunk->type[2] = w.bytes.b3;
  chunk->type[3] = w.bytes.b4;

  u8 *data = malloc(chunk->len);
  for (u64 i = 0; i < chunk->len; i++)
    data[i] = fgetc(f);
  chunk->data = data;

  fill_word32(w);
  chunk->check = w.word;
}
