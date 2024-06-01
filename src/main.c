#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "args.h"
#include "types.h"
#include "methods.h"

int main(int argc, char** argv) {
    /* Parse command line arguments */
    Arguments args = parse_arguments(argc, argv);
    ProcessingInfo info = { .volume = args.volume, .panning = args.panning, .phase_offset = args.phase_offset };

    /* Generate wav header from stdin */
    WavFileHeader header = read_wav_stream(stdin);
    if (args.verbose) { print_wav_header(stderr, header); }
    if (verify_format(stderr, header)) { return EXIT_FAILURE; }

    uint32_t data_length = header.Data.Size.w;
    uint32_t sample_rate = header.Format.SampleRate.w;
    uint16_t block_size = header.Format.BlockAlign.hw;
    uint16_t channels = header.Format.Channels.hw;
    uint16_t bytes_per_channel = block_size / channels;

    /* Calculate number of samples to store for phase offset */
    float phase_offset = fabsf(info.phase_offset) / 2.0;
    size_t one_sample_second = sample_rate * block_size;

    size_t samples_length_unaligned = one_sample_second * phase_offset;
    size_t samples_length = samples_length_unaligned - (samples_length_unaligned % block_size);

    ByteAddressableSignedHalfWord samples[samples_length + block_size];
    memset(samples, 0, samples_length + block_size);

    /* Write wav header to stdout */
    write_wav_header(stdout, header);

    /* Process data stream */
    for (uint32_t block_index = 0; block_index < data_length; block_index += block_size) {
        size_t sample_index = (block_index / channels) % samples_length;

        /* Calculate index to phase shift to */
        size_t phase_index = (sample_index + channels) % samples_length;

        for (uint16_t channel = 0; channel < channels; channel++) {
            ByteAddressableSignedHalfWord block;

            /* Read block in one byte at a time */
            for (uint16_t nibble = 0; nibble < bytes_per_channel; nibble++) {
                block.b[nibble] = fgetc(stdin);
            }

            /* Store block for later use */
            samples[sample_index + channel] = block;

            /* Process panning and phase */
            if (channel % 2 == 0) {
                if (info.phase_offset > 0) { block.sw = samples[phase_index + channel].sw; }
                if (info.panning > 0) { block.sw *= 1 - info.panning; }
            }

            else {
                if (info.phase_offset < 0) { block.sw = samples[phase_index + channel].sw; }
                if (info.panning < 0) { block.sw *= 1 + info.panning; }
            }

            /* Process volume */
            block.sw *= info.volume;

            /* Write channel block to stdout */
            for (uint16_t nibble = 0; nibble < bytes_per_channel; nibble++) {
                fputc(block.b[nibble], stdout);
            }
        }
    }

    return EXIT_SUCCESS;
}
