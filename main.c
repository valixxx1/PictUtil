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

#include "imgtype/imgtype.h"
#include "helpmenu/help.h"
#include "bswap/bswap.h"
#include "logg/logg.h"
#include "png/ihdr.h"
#include "types.h"

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>

#define VERSION "v0.0.2"

int main(int argc, char *argv[])
{
  struct ihdr ihdr;
  t32 getopt_res;
  t8 fmt;
  fl *f;

  bool size_flag = 0, help_flag = 0;

  while ((getopt_res = getopt(argc, argv, "hs")) != -1) {
    switch (getopt_res) {
      case 'h':
        help_flag = 1;
        break;
      case 's':
        size_flag = 1;
        break;
    }
  }

  if (help_flag)
    helpmenu(VERSION);
  else if (size_flag) {
    f = fopen(argv[optind], "rb");

    if (!f) {
      perror("Image wasn't opened");
      return 2;
    }

    fmt = imgtype(f);

    /* If PNG */
    if (fmt == 'p') {
      logg("log.txt", "PNG\n");
      fread(&ihdr, sizeof(ihdr), 1, f);
      bswap_ihdr(&ihdr);
    }

    printf("Width: %u\nHeight: %u\n", ihdr.width, ihdr.height);

    fclose(f);
  }

  return 0;
}
