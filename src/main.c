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

    /* For some reason I have more bytes? */
    fputc(ch, stdout);
    ch = fgetc(stdin);

    fputc(ch, stdout);
    ch = fgetc(stdin);


    DataHeader data_header;

    data_header.Id.b[0] = ch;
    fputc(ch, stdout);

    ch = fgetc(stdin);
    data_header.Id.b[1] = ch;
    fputc(ch, stdout);

    ch = fgetc(stdin);
    data_header.Id.b[2] = ch;
    fputc(ch, stdout);

    ch = fgetc(stdin);
    data_header.Id.b[3] = ch;
    fputc(ch, stdout);

    ch = fgetc(stdin);
    data_header.Size.b[0] = ch;
    fputc(ch, stdout);

    ch = fgetc(stdin);
    data_header.Size.b[1] = ch;
    fputc(ch, stdout);

    ch = fgetc(stdin);
    data_header.Size.b[2] = ch;
    fputc(ch, stdout);

    ch = fgetc(stdin);
    data_header.Size.b[3] = ch;
    fputc(ch, stdout);

    ch = fgetc(stdin);

    fprintf(stderr, "DataId: %14.*s \n", (int)sizeof(data_header.Id), data_header.Id.b);
    fprintf(stderr, "DataSize: %12u\n", data_header.Size.w);
    fprintf(stderr, "Diff: %16u\n", header.Header.Size.w - data_header.Size.w);
    fprintf(stderr, "sizeofHeader: %8zu\n", sizeof(header));

    /* Diff: 38, sizeofHeader: 36 */
    fprintf(stderr, "Errm where the hell these two bytes coming from\n");

    do {
        fputc(ch, stdout);
        i++;

    /* Must be do..while here
     * as ch is still holding a character we need */
    } while ((ch = fgetc(stdin)) != EOF); //&& i < header.Header.Size.w);

    return EXIT_SUCCESS;
}
