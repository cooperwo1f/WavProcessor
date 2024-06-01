#ifndef WAV_METHODS_H
#define WAV_METHODS_H

#include <stdio.h>
#include <stdint.h>
#include "types.h"

WavFileHeader read_wav_stream(FILE* fd);
WavFileHeader read_wav_file(FILE* fp);
WavFileHeader read_wav_arr(uint32_t* buf, size_t len);

size_t write_wav_header(FILE* fd, WavFileHeader header);
int verify_format(FILE* fd, WavFileHeader header);
void print_wav_header(FILE* fd, WavFileHeader wav);

#endif /* WAV_METHODS_H */
