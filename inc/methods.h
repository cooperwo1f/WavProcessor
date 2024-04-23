#ifndef WAV_METHODS_H
#define WAV_METHODS_H

#include <stdio.h>
#include <stdint.h>
#include "types.h"

WavFileHeader read_wav_file(FILE* fp);
WavFileHeader read_wav_arr(uint32_t* buf, size_t len);

void process_sample(FILE* fd, ProcessingInfo info, WavFileHeader header, ByteAddressableSignedWord samples[][header.Format.Channels.hw], size_t index);
int verify_format(FILE* fd, WavFileHeader header);

void print_wav_header(FILE* fd, WavFileHeader wav);
void debug_array(FILE* fd, int* buf, size_t len);

#endif /* WAV_METHODS_H */
