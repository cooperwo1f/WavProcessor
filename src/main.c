#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "args.h"
#include "types.h"
#include "methods.h"

int main(int argc, char** argv) {
    Arguments args = parse_arguments(argc, argv);

    ProcessingInfo info = { .volume = args.volume, .panning = args.panning, .phase_offset = args.phase_offset };
    uint32_t header_buf[sizeof(WavFileHeader)];
    size_t i = 0;
    int ch;


    /* Fill character buffer with number of bytes expected in wav header */
    while ((ch = fgetc(stdin)) != EOF && i < sizeof(WavFileHeader)) {
        header_buf[i++] = (uint32_t)ch;
        fputc(ch, stdout);
    }


    /* Two bytes of padding? */
    i++;
    fputc(ch, stdout);

    i++;
    fputc(fgetc(stdin), stdout);


    /* Generate wav header from filled out array */
    WavFileHeader header = read_wav_arr(header_buf, sizeof(header_buf)/sizeof(int));
    if (verify_format(stderr, header) != EXIT_SUCCESS) { return EXIT_FAILURE; }
    if (args.verbose) { print_wav_header(stderr, header); }

    /* Process raw data stream */
    while ((ch = fgetc(stdin)) != EOF) {
        fputc(process_sample(info, header, ch, i++), stdout);
    }


    return EXIT_SUCCESS;
}
