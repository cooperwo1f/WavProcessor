#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "types.h"
#include "methods.h"

int main(int argc, char** argv) {
    uint32_t header_buf[sizeof(WavFileHeader)];
    size_t i = 0;
    int ch;

    /* Fill character buffer with number of bytes expected in wav header */
    while ((ch = fgetc(stdin)) != EOF && i < sizeof(WavFileHeader)) {
        header_buf[i++] = (uint32_t)ch;
        fputc(ch, stdout);
    }

    /* Generate wav header from out filled array */
    WavFileHeader header = read_wav_arr(header_buf, sizeof(header_buf)/sizeof(int));
    if (verify_format(stderr, header) != EXIT_SUCCESS) { return EXIT_FAILURE; }
    print_wav_header(stderr, header);

    /* TODO: take out data chunk so can mess with other things */

    do {
        fputc(ch, stdout);
        i++;

    /* Must be do..while here
     * as ch is still holding a character we need */
    } while ((ch = fgetc(stdin)) != EOF && i < header.Header.Size.w);

    return EXIT_SUCCESS;
}
