#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "methods.h"
#include "types.h"

Header default_header() {
    return (Header){
        .Size.w = 0,
        .Id.b[0] = 'N',
        .Id.b[1] = 'O',
        .Id.b[2] = 'N',
        .Id.b[3] = 'E',
        .Data.b[0] = 'N',
        .Data.b[1] = 'O',
        .Data.b[2] = 'N',
        .Data.b[3] = 'E',
    };
}

Header read_header_file(FILE* fp) {
    Header header = default_header();

    fread(&header.Id.w,   sizeof(header.Id),   1, fp);
    fread(&header.Size.w, sizeof(header.Size), 1, fp);
    fread(&header.Data.w, sizeof(header.Data), 1, fp);

    return header;
}

Header read_header_arr(uint32_t* buf, size_t len) {
    /* Verify array will fit into header, otherwise return empty header */
    if (sizeof(Header) > len) return default_header();

    return (Header){
        .Id.b[0] = buf[0],
        .Id.b[1] = buf[1],
        .Id.b[2] = buf[2],
        .Id.b[3] = buf[3],

        .Size.b[0] = buf[4],
        .Size.b[1] = buf[5],
        .Size.b[2] = buf[6],
        .Size.b[3] = buf[7],

        .Data.b[0] = buf[8],
        .Data.b[1] = buf[9],
        .Data.b[2] = buf[10],
        .Data.b[3] = buf[11]
    };
}

void print_header(FILE* fd, Header header) {
    fprintf(fd, "HeaderId: %12.*s \n", (int)sizeof(header.Id), header.Id.b);
    fprintf(fd, "HeaderSize: %10u \n", header.Size.w);
    fprintf(fd, "HeaderData: %10.*s \n", (int)sizeof(header.Data), header.Data.b);
}

Format default_format() {
    return (Format){
        .Id.b[0] = 'N',
        .Id.b[1] = 'O',
        .Id.b[2] = 'N',
        .Id.b[3] = 'E',
        .Size.w = 0,
        .Format.hw = 0,
        .Channels.hw = 0,
        .SampleRate.w = 0,
        .ByteRate.w = 0,
        .BlockAlign.hw = 0,
        .BitsPerSample.hw = 0
    };
}

Format read_format_file(FILE* fp) {
    Format format = default_format();

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
    /* Verify array will fit into format, otherwise return empty format */
    if (sizeof(Format) > len) return default_format();

    return (Format){
        .Id.b[0] = buf[0],
        .Id.b[1] = buf[1],
        .Id.b[2] = buf[2],
        .Id.b[3] = buf[3],

        .Size.b[0] = buf[4],
        .Size.b[1] = buf[5],
        .Size.b[2] = buf[6],
        .Size.b[3] = buf[7],

        .Format.b[0] = buf[8],
        .Format.b[1] = buf[9],

        .Channels.b[0] = buf[10],
        .Channels.b[1] = buf[11],

        .SampleRate.b[0] = buf[12],
        .SampleRate.b[1] = buf[13],
        .SampleRate.b[2] = buf[14],
        .SampleRate.b[3] = buf[15],

        .ByteRate.b[0] = buf[16],
        .ByteRate.b[1] = buf[17],
        .ByteRate.b[2] = buf[18],
        .ByteRate.b[3] = buf[19],

        .BlockAlign.b[0] = buf[20],
        .BlockAlign.b[1] = buf[21],

        .BitsPerSample.b[0] = buf[22],
        .BitsPerSample.b[1] = buf[23]
    };
}

void print_format(FILE* fd, Format format) {
    fprintf(fd, "FormatId: %12.*s \n", (int)sizeof(format.Id), format.Id.b);
    fprintf(fd, "FormatSize: %10u\n", format.Size.w);
    fprintf(fd, "Format: %14u\n", format.Format.hw);
    fprintf(fd, "Channels: %12u\n", format.Channels.hw);
    fprintf(fd, "SampleRate: %10u\n", format.SampleRate.w);
    fprintf(fd, "ByteRate: %12u\n", format.ByteRate.w);
    fprintf(fd, "BlockAlign: %10u\n", format.BlockAlign.hw);
    fprintf(fd, "BitsPerSample: %7u\n", format.BitsPerSample.hw);
}

Data default_data_header() {
    return (Data){
        .Size.w = 0,
        .Id.b[0] = 'N',
        .Id.b[1] = 'O',
        .Id.b[2] = 'N',
        .Id.b[3] = 'E'
    };
}

Data read_data_header_file(FILE* fp) {
    Data data_header = default_data_header();

    fread(&data_header.Id.w,   sizeof(data_header.Id),   1, fp);
    fread(&data_header.Size.w, sizeof(data_header.Size), 1, fp);

    return data_header;
}

Data read_data_header_arr(uint32_t* buf, size_t len) {
    /* Verify array will fit into data_header, otherwise return empty data_header */
    if (sizeof(Data) > len) return default_data_header();

    return (Data){
        .Id.b[0] = buf[0],
        .Id.b[1] = buf[1],
        .Id.b[2] = buf[2],
        .Id.b[3] = buf[3],

        .Size.b[0] = buf[4],
        .Size.b[1] = buf[5],
        .Size.b[2] = buf[6],
        .Size.b[3] = buf[7],
    };
}

void print_data_header(FILE* fd, Data data_header) {
    fprintf(fd, "DataId: %14.*s \n", (int)sizeof(data_header.Id), data_header.Id.b);
    fprintf(fd, "DataSize: %12u \n", data_header.Size.w);
}

WavFileHeader default_wav_header() {
    return (WavFileHeader){
        .Header = default_header(),
        .Format = default_format(),
        .Data = default_data_header()
    };
}

WavFileHeader read_wav_file(FILE* fp) {
    return (WavFileHeader){
        .Header = read_header_file(fp),
        .Format = read_format_file(fp),
        .Data = read_data_header_file(fp)
    };
}

WavFileHeader read_wav_arr(uint32_t* buf, size_t len) {
    /* If array does not match header, return empty WavFileHeader */
    if (len != (sizeof(WavFileHeader))) { return default_wav_header(); }

    size_t format_offset = sizeof(Header);
    size_t data_offset = format_offset + sizeof(Format) - 2; /* Padding compensation */

    return (WavFileHeader){
        .Header = read_header_arr(buf, len),
        .Format = read_format_arr(buf + format_offset, len - format_offset),
        .Data = read_data_header_arr(buf + data_offset, len - data_offset)
    };
}

int is_RIFF_format(FILE* fp) {
    char chunk_id[sizeof(((Header*)0)->Id)];

    fread(chunk_id, sizeof(chunk_id), 1, fp);
    rewind(fp);

    return strcmp(chunk_id, "RIFF");
}

int verify_format(FILE* fd, WavFileHeader header) {
  if (strncmp((char*)header.Header.Id.b, "RIFF", (int)sizeof(header.Header.Id.w)) != 0) {
    fprintf(fd, "File must be RIFF format, may have been error reading stream [Header.Id=%.*s]", (int)sizeof(header.Header.Data), header.Header.Id.b);
    return EXIT_FAILURE;
  }

  if (strncmp((char*)header.Header.Data.b, "WAVE", (int)sizeof(header.Header.Data.w)) != 0) {
    fprintf(fd, "Error reading stream, expected header data to contain 'WAVE' [Header.Data=%.*s]", (int)sizeof(header.Header.Data), header.Header.Data.b);
    return EXIT_FAILURE;
  }

  if (header.Format.Format.hw != PCM) {
    fprintf(fd, "File must contain uncompressed PCM stream [Format.Format=%u]", header.Format.Format.hw);
    return EXIT_FAILURE;
  }

  if (strncmp((char*)header.Data.Id.b, "data", (int)sizeof(header.Data.Id)) != 0) {
    fprintf(fd, "Error reading stream, expected data header id to be 'data' [Data.Id=%.*s]", (int)sizeof(header.Data.Id), header.Data.Id.b);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void print_wav_header(FILE* fd, WavFileHeader wav) {
    print_header(fd, wav.Header);
    fputc('\n', stderr);
    print_format(fd, wav.Format);
    fputc('\n', stderr);
    print_data_header(fd, wav.Data);
    fputc('\n', stderr);
}

void debug_array(FILE* fd, int* buf, size_t len) {
  for (size_t i = 0; i < len; i++) {
      if (i % 8 == 0) { fputc('\n', fd); }
      fprintf(fd, "%10c", (char)buf[i]);
  }

  fputc('\n', fd);
  fputc('\n', fd);
}

int process_phase(int sample) {
    return sample;
}

int process_panning(int sample) {
    return sample;
}

int process_volume(int sample, float volume) {
    return sample;
}

/* Needs to take in current sample, apply process as specified in process_info, and return appropriate sample */
/* TODO: explore what happens when sample index reaches header.Data.Size.w */
int process_sample(ProcessingInfo info, WavFileHeader header, int sample, size_t index) {
    size_t start_index = header.Header.Size.w - header.Data.Size.w + sizeof(header.Data) + 4;

    size_t sample_index = index - start_index;
    size_t array_index = sample_index / header.Format.BlockAlign.hw;

    size_t channel_num = sample_index % header.Format.Channels.hw;
    size_t nibble_num = (sample_index / header.Format.Channels.hw) % (header.Format.BlockAlign.hw / header.Format.Channels.hw);

    sample = process_phase(sample);
    sample = process_panning(sample);
    sample = process_volume(sample, info.volume);

    return sample;

    /* No idea how this would work with 18-bit PCM */
    /* uint16_t nibble_num = 0; */
    /* uint16_t channel_num = 0; */

    /* /\* SampleRate = 1 second of samples *\/ */
    /* size_t num_of_seconds = 2; */
    /* size_t samples_per_second = header.Format.SampleRate.w * header.Format.BlockAlign.hw; */
    /* size_t samples_to_store = samples_per_second * num_of_seconds; */

    /* size_t sample_index = 0; */
    /* ByteAddressableSignedWord samples[samples_to_store][header.Format.Channels.hw]; */

    /*     size_t array_index = sample_index / header.Format.BlockAlign.hw; */

    /*     if (sample_index % header.Format.Channels.hw == 0) { channel_num = 0; nibble_num++; } */
    /*     if (sample_index % header.Format.BlockAlign.hw == 0) { nibble_num = 0; } */

    /*     samples[array_index % samples_to_store][channel_num].b[nibble_num] = fgetc(stdin); */

    /*     if (array_index > 100) */
    /*         fputc(samples[(sample_index/header.Format.BlockAlign.hw) % samples_to_store][channel_num].b[nibble_num], stdout); */

    /*     i++; */
    /*     sample_index++; */
    /*     channel_num++; */

}
