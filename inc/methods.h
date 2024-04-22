#ifndef WAV_METHODS_H
#define WAV_METHODS_H

#include <stdio.h>
#include <stdint.h>
#include "types.h"

WavFileHeader read_wav_file(FILE* fp);
WavFileHeader read_wav_arr(uint32_t* buf, size_t len);

int verify_format(WavFileHeader header);
void print_wav_header(WavFileHeader wav);

void debug_array(int* buf, size_t len);

#endif /* WAV_METHODS_H */
