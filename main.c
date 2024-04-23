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

#include "bswap/bswap.h"
#include "png/ihdr.h"
#include "png/sign.h"
#include "types.h"

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>

#define VERSION "v0.0.1"

int main(int argc, char *argv[])
{
  struct ihdr ihdr;
  int getopt_res;
  u64 sign;
  fl *f;

  bool size_flag = false, help_flag = false;

  while ((getopt_res = getopt(argc, argv, "hs")) != -1) {
    switch (getopt_res) {
      case 'h':
        help_flag = true;
        break;
      case 's':
        size_flag = true;
        break;
    }
  }


  if (help_flag) {
    printf("A photo redactor.\nVersion: %s\n\nOptions:\n\t-h: Write this help menu.\n\t-s: Print size of the image.\n", VERSION);
  } else if (size_flag) {
    f = fopen(argv[optind], "rb");

    if (!f) {
      perror("Image wasn't opened");
      return 2;
    }

    fread(&sign, 8, 1, f);
    bswap(&sign, 8);
    if (sign == PNG_SIGN) {
      fread(&ihdr, sizeof(ihdr), 1, f);
      bswap_ihdr(&ihdr);
    }

    printf("Width: %u\nHeight: %u\n", ihdr.width, ihdr.height);

    fclose(f);
  }

  return 0;
}
