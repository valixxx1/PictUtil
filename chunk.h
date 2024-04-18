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

#ifndef CHUNK_H
#define CHUNK_H

#include "types.h"
#include <stdlib.h>
#include <string.h>

struct chunk
{
  u32  len;     /* Length of data */
  char type[4]; /* Type of chunk  */
  u8   *data;   /* Data           */
  u32  check;   /* Checksum       */
};

void chsumtable(u32 *table);
u32 checksum32(u32 *table, u8 *b, u64 len);

u8* chunk_checksum_buf(struct chunk *chunk);
void chunk_checksum(struct chunk *chunk);

void chunk_debug(struct chunk *chunk);

#endif