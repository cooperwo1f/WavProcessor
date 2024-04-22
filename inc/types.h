#ifndef WAV_TYPES_H
#define WAV_TYPES_H

#include <stdint.h>

#define PCM 1

typedef union _ByteAddressableWord {
    uint32_t w;
    uint8_t b[sizeof(uint32_t)];
} ByteAddressableWord;

typedef union _ByteAddressableHalfWord {
    uint16_t hw;
    uint8_t b[sizeof(uint16_t)];
} ByteAddressableHalfWord;


typedef struct _Header {
    ByteAddressableWord Id;                 /* Contains the letters "RIFF" */
    ByteAddressableWord Size;               /* Size of the entire chunk */
    ByteAddressableWord Data;               /* Contains the letter "WAVE" */
} Header;

typedef struct _Format {
    ByteAddressableWord Id;                 /* Contains the letters "fmt " */
    ByteAddressableWord Size;               /* 16 or 18 for PCM.  This is the size of the rest of the Subchunk which follows this number. */
    ByteAddressableHalfWord Format;         /* PCM = 1 (i.e. Linear quantization) Values other than 1 indicate some form of compression. */
    ByteAddressableHalfWord Channels;       /* Mono = 1, Stereo = 2, etc. */
    ByteAddressableWord SampleRate;         /* 8000, 44100, etc. */
    ByteAddressableWord ByteRate;           /* == SampleRate * NumChannels * BitsPerSample/8 */
    ByteAddressableHalfWord BlockAlign;     /* == NumChannels * BitsPerSample/8. The number of bytes for one sample including all channels */
    ByteAddressableHalfWord BitsPerSample;  /* 8 bits = 8, 16 bits = 16, etc. */
} Format;

typedef struct _DataHeader {
    ByteAddressableWord Id;                 /* Contains the letters "data" */
    ByteAddressableWord Size;               /* Size of the data chunk */
} DataHeader;

typedef struct _WavFileHeader {
    Header Header;
    Format Format;
} WavFileHeader;

#endif /* WAV_TYPES_H */
