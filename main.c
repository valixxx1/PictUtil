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

#include <stdio.h>
#include "chunk.h"
#include "types.h"
#include "errs.h"
#include "parsing.h"

t32
main(t32 argc, char *argv[])
{
  struct chunk chunk;
  char ch;
  fl *f;

  if (argc < 2)
    err(_2fewargs, -1);

  f = fopen(argv[1], "rb");

  if (!f)
    err(fnread, -2);

  for (u64 i = 0; i < 8; i++)
    {
      ch = fgetc(f);
      pbyte(ch);
    }
  putchar('\n');

  read_chunk(f, &chunk);
  //chunk_debug(&chunk);
  printf("Width: %d\n", (u32) chunk.data[0]);
  free(chunk.data);

  return 0;
}
