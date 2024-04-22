#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "methods.h"
#include "types.h"

Header read_header_file(FILE* fp) {
    Header header;

    fread(&header.Id.w,   sizeof(header.Id),   1, fp);
    fread(&header.Size.w, sizeof(header.Size), 1, fp);
    fread(&header.Data.w, sizeof(header.Data), 1, fp);

    return header;
}

Header read_header_arr(uint32_t* buf, size_t len) {
    Header header;

    /* Verify array will fit into header, otherwise return empty header */
    if (sizeof(Header) > len) return header;

    header.Id.b[0] = buf[0];
    header.Id.b[1] = buf[1];
    header.Id.b[2] = buf[2];
    header.Id.b[3] = buf[3];

    header.Size.b[0] = buf[4];
    header.Size.b[1] = buf[5];
    header.Size.b[2] = buf[6];
    header.Size.b[3] = buf[7];

    header.Data.b[0] = buf[8];
    header.Data.b[1] = buf[9];
    header.Data.b[2] = buf[10];
    header.Data.b[3] = buf[11];

    return header;
}

void print_header(Header header) {
    printf("HeaderId: %12.*s \n", (int)sizeof(header.Id.w), header.Id.b);
    printf("HeaderSize: %10u \n", header.Size.w);
    printf("HeaderData: %10.*s \n", (int)sizeof(header.Data.w), header.Data.b);
}

Format read_format_file(FILE* fp) {
    Format format;

    fread(&format.Id.w,             sizeof(format.Id),            1, fp);
    fread(&format.Size.w,           sizeof(format.Size),          1, fp);
    fread(&format.Format.hw,        sizeof(format.Format),        1, fp);
    fread(&format.Channels.hw,      sizeof(format.Channels),      1, fp);
    fread(&format.SampleRate.w,     sizeof(format.SampleRate),    1, fp);
    fread(&format.ByteRate.w,       sizeof(format.ByteRate),      1, fp);
    fread(&format.BlockAlign.hw,    sizeof(format.BlockAlign),    1, fp);
    fread(&format.BitsPerSample.hw, sizeof(format.BitsPerSample), 1, fp);

    return format;
}

Format read_format_arr(uint32_t* buf, size_t len) {
    Format format;

    /* Verify array will fit into format, otherwise return empty format */
    if (sizeof(Format) > len) return format;

    format.Id.b[0] = buf[0];
    format.Id.b[1] = buf[1];
    format.Id.b[2] = buf[2];
    format.Id.b[3] = buf[3];

    format.Size.b[0] = buf[4];
    format.Size.b[1] = buf[5];
    format.Size.b[2] = buf[6];
    format.Size.b[3] = buf[7];

    format.Format.b[0] = buf[8];
    format.Format.b[1] = buf[9];

    format.Channels.b[0] = buf[10];
    format.Channels.b[1] = buf[11];

    format.SampleRate.b[0] = buf[12];
    format.SampleRate.b[1] = buf[13];
    format.SampleRate.b[2] = buf[14];
    format.SampleRate.b[3] = buf[15];

    format.ByteRate.b[0] = buf[16];
    format.ByteRate.b[1] = buf[17];
    format.ByteRate.b[2] = buf[18];
    format.ByteRate.b[3] = buf[19];

    format.BlockAlign.b[0] = buf[20];
    format.BlockAlign.b[1] = buf[21];

    format.BitsPerSample.b[0] = buf[22];
    format.BitsPerSample.b[1] = buf[23];

    return format;
}

void print_format(Format format) {
    printf("FormatId: %12.*s \n", (int)sizeof(format.Id.w), format.Id.b);
    printf("FormatSize: %10u\n", format.Size.w);
    printf("Format: %14u\n", format.Format.hw);
    printf("Channels: %12u\n", format.Channels.hw);
    printf("SampleRate: %10u\n", format.SampleRate.w);
    printf("ByteRate: %12u\n", format.ByteRate.w);
    printf("BlockAlign: %10u\n", format.BlockAlign.hw);
    printf("BitsPerSample: %7u\n\n", format.BitsPerSample.hw);
}

WavFileHeader read_wav_file(FILE* fp) {
    WavFileHeader wav;

    wav.Header = read_header_file(fp);
    wav.Format = read_format_file(fp);

    return wav;
}

WavFileHeader read_wav_arr(uint32_t* buf, size_t len) {
    WavFileHeader wav;

    /* If array does not fill header, return empty WavFileHeader */
    if ((sizeof(WavFileHeader)) > len) { return wav; }

    size_t header_offset = 0;
    size_t format_offset = sizeof(Header) + header_offset;

    wav.Header = read_header_arr(buf + header_offset, len - header_offset);
    wav.Format = read_format_arr(buf + format_offset, len - format_offset);

    return wav;
}

int is_RIFF_format(FILE* fp) {
    char chunk_id[sizeof(((Header*)0)->Id)];

    fread(chunk_id, sizeof(chunk_id), 1, fp);
    rewind(fp);

    return strcmp(chunk_id, "RIFF");
}

int verify_format(WavFileHeader header) {
  if (strncmp((char*)header.Header.Id.b, "RIFF", (int)sizeof(header.Header.Id.w)) != 0) {
    fprintf(stderr, "File must be RIFF format, may have been error reading stream [Header.Id=%.*s]", (int)sizeof(header.Header.Data.w), header.Header.Id.b);
    return EXIT_FAILURE;
  }

  if (strncmp((char*)header.Header.Data.b, "WAVE", (int)sizeof(header.Header.Data.w)) != 0) {
    fprintf(stderr, "Error reading stream, expected header data to contain 'WAVE' [Header.Data=%.*s]", (int)sizeof(header.Header.Data.w), header.Header.Data.b);
    return EXIT_FAILURE;
  }

  if (header.Format.Format.hw != 1) {
    fprintf(stderr, "File must contain uncompressed PCM stream [Format.Format=%u]", header.Format.Format.hw);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void print_wav_header(WavFileHeader wav) {
    print_header(wav.Header);
    print_format(wav.Format);
}

void debug_array(int* buf, size_t len) {
  for (size_t i = 0; i < len; i++) {
      if (i % 8 == 0) { fputc('\n', stdout); }
      printf("%10c", (char)buf[i]);
  }

  fputc('\n', stdout);
  fputc('\n', stdout);
}
