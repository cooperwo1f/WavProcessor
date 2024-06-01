#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "methods.h"
#include "types.h"

size_t putbashw(ByteAddressableSignedHalfWord w, FILE* fd) {
    size_t i;
    for (i = 0; i < sizeof(ByteAddressableSignedHalfWord); i++) {
        fputc(w.b[i], fd);
    }
    return i;
}

size_t putbasw(ByteAddressableSignedWord w, FILE* fd) {
    size_t i;
    for (i = 0; i < sizeof(ByteAddressableSignedWord); i++) {
        fputc(w.b[i], fd);
    }
    return i;
}

size_t putbahw(ByteAddressableHalfWord w, FILE* fd) {
    size_t i;
    for (i = 0; i < sizeof(ByteAddressableHalfWord); i++) {
        fputc(w.b[i], fd);
    }
    return i;
}

size_t putbaw(ByteAddressableWord w, FILE* fd) {
    size_t i;
    for (i = 0; i < sizeof(ByteAddressableWord); i++) {
        fputc(w.b[i], fd);
    }
    return i;
}

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

    fread(&header.Id, sizeof(header.Id), 1, fp);
    fread(&header.Size, sizeof(header.Size), 1, fp);
    fread(&header.Data, sizeof(header.Data), 1, fp);

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

size_t write_header(FILE* fd, Header header) {
    size_t i = 0;
    i += putbaw(header.Id, fd);
    i += putbaw(header.Size, fd);
    i += putbaw(header.Data, fd);
    return i;
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

    fread(&format.Id, sizeof(format.Id), 1, fp);
    fread(&format.Size, sizeof(format.Size), 1, fp);
    fread(&format.Format, sizeof(format.Format), 1, fp);
    fread(&format.Channels, sizeof(format.Channels), 1, fp);
    fread(&format.SampleRate, sizeof(format.SampleRate), 1, fp);
    fread(&format.ByteRate, sizeof(format.ByteRate), 1, fp);
    fread(&format.BlockAlign, sizeof(format.BlockAlign), 1, fp);
    fread(&format.BitsPerSample, sizeof(format.BitsPerSample), 1, fp);

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

size_t write_format(FILE* fd, Format format) {
    size_t i = 0;
    i += putbaw(format.Id, fd);
    i += putbaw(format.Size, fd);
    i += putbahw(format.Format, fd);
    i += putbahw(format.Channels, fd);
    i += putbaw(format.SampleRate, fd);
    i += putbaw(format.ByteRate, fd);
    i += putbahw(format.BlockAlign, fd);
    i += putbahw(format.BitsPerSample, fd);
    return i;
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
    Data data = default_data_header();

    fread(&data.Id, sizeof(data.Id), 1, fp);
    fread(&data.Size, sizeof(data.Size), 1, fp);

    return data;
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

size_t write_data_header(FILE* fd, Data data) {
    size_t i = 0;
    i += putbaw(data.Id, fd);
    i += putbaw(data.Size, fd);
    return i;
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

WavFileHeader read_wav_stream(FILE* fd) {
    uint32_t buf[sizeof(WavFileHeader)];
    size_t i = 0;

    while ((buf[i++] = fgetc(fd)) != EOF && i < sizeof(WavFileHeader));

    /* If EOF was reached early, return empty WavFileHeader */
    if (i != (sizeof(WavFileHeader))) { return default_wav_header(); }

    size_t format_offset = sizeof(Header);
    size_t data_offset = format_offset + sizeof(Format);

    return (WavFileHeader){
        .Header = read_header_arr(buf, sizeof(WavFileHeader)),
        .Format = read_format_arr(buf + format_offset, sizeof(WavFileHeader) - format_offset),
        .Data = read_data_header_arr(buf + data_offset, sizeof(WavFileHeader) - data_offset)
    };
}

WavFileHeader read_wav_file(FILE* fp) {
    if (fp == NULL) { return default_wav_header(); }

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
    size_t data_offset = format_offset + sizeof(Format);

    return (WavFileHeader){
        .Header = read_header_arr(buf, len),
        .Format = read_format_arr(buf + format_offset, len - format_offset),
        .Data = read_data_header_arr(buf + data_offset, len - data_offset)
    };
}

size_t write_wav_header(FILE* fd, WavFileHeader header) {
    size_t i = 0;
    i += write_header(fd, header.Header);
    i += write_format(fd, header.Format);
    i += write_data_header(fd, header.Data);
    return i;
}

void print_wav_header(FILE* fd, WavFileHeader wav) {
    print_header(fd, wav.Header);
    fputc('\n', stderr);
    print_format(fd, wav.Format);
    fputc('\n', stderr);
    print_data_header(fd, wav.Data);
    fputc('\n', stderr);
}

int verify_format(FILE* fd, WavFileHeader header) {
  if (strncmp((char*)header.Header.Id.b, "RIFF", (int)sizeof(header.Header.Id.w)) != 0) {
    fprintf(fd, "File must be RIFF format, may have been error reading stream [Header.Id=%.*s]\n", (int)sizeof(header.Header.Data), header.Header.Id.b);
    return 1;
  }

  if (strncmp((char*)header.Header.Data.b, "WAVE", (int)sizeof(header.Header.Data.w)) != 0) {
    fprintf(fd, "Error reading stream, expected header data to contain 'WAVE' [Header.Data=%.*s]\n", (int)sizeof(header.Header.Data), header.Header.Data.b);
    return 1;
  }

  if (header.Format.Format.hw != PCM) {
    fprintf(fd, "File must contain uncompressed PCM stream [Format.Format=%u]\n", header.Format.Format.hw);
    return 1;
  }

  if (strncmp((char*)header.Data.Id.b, "data", (int)sizeof(header.Data.Id)) != 0) {
    fprintf(fd, "Error reading stream, expected data header id to be 'data' [Data.Id=%.*s]\n", (int)sizeof(header.Data.Id), header.Data.Id.b);
    return 1;
  }

  return 0;
}

void debug_array(FILE* fd, int* buf, size_t len) {
  for (size_t i = 0; i < len; i++) {
      if (i % 8 == 0) { fputc('\n', fd); }
      fprintf(fd, "%10c", (char)buf[i]);
  }

  fputc('\n', fd);
  fputc('\n', fd);
}
