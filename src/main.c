#include <math.h>
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

    size_t samples_num = (header.Format.SampleRate.w * header.Format.BlockAlign.hw * fabsf(info.phase_offset)) + 1;
    ByteAddressableSignedWord samples[samples_num][header.Format.Channels.hw];

    size_t prev_array_index = 0;
    size_t start_index = header.Header.Size.w - header.Data.Size.w + sizeof(header.Data) + 4;

    /* Process raw data stream */
    /* TODO: explore what happens when sample index reaches header.Data.Size.w */
    while ((ch = fgetc(stdin)) != EOF) {
        size_t sample_index = i++ - start_index;

        size_t array_index = (sample_index / header.Format.BlockAlign.hw) % samples_num;
        size_t channel_num = sample_index % header.Format.Channels.hw;
        size_t nibble_num = (sample_index / header.Format.Channels.hw) % (header.Format.BlockAlign.hw / header.Format.Channels.hw);

        if (array_index != prev_array_index) {
            process_sample(stdout, info, header, samples, prev_array_index);
        }

        samples[array_index][channel_num].b[nibble_num] = ch;
        prev_array_index = array_index;
    }

    process_sample(stdout, info, header, samples, prev_array_index);

    return EXIT_SUCCESS;
}
