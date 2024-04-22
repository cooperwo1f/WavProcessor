#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "types.h"
#include "methods.h"

int main(int argc, char** argv) {
  size_t i = 0;

  int header_buf[sizeof(WavFileHeader)];
  int ch;

  /* Fill character buffer with number of bytes expected in wav header */
  while ((ch = fgetc(stdin)) != EOF) {
    if (i > sizeof(WavFileHeader)) { break; }
    header_buf[i++] = ch;
  }

  /* Generate wav header from out filled array */
  WavFileHeader header = read_wav_arr((uint32_t*)header_buf, sizeof(header_buf)/sizeof(int));
  if (verify_format(header) != EXIT_SUCCESS) { return EXIT_FAILURE; }


  while ((ch = fgetc(stdin)) != EOF) {
    if (i++ > header.Header.Size.w) { break; }

    /* Do something here */

  }

  /* No newline here causes abort trap 6 */
  fputc('\n', stdout);

  return EXIT_SUCCESS;
}
