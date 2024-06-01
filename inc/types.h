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

typedef union _ByteAddressableSignedWord {
    int32_t sw;
    uint8_t b[sizeof(int32_t)];
} ByteAddressableSignedWord;

typedef union _ByteAddressableSignedHalfWord {
    int16_t sw;
    uint8_t b[sizeof(int16_t)];
} ByteAddressableSignedHalfWord;


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

typedef struct _Data {
    ByteAddressableWord Id;                 /* Contains the letters "data" */
    ByteAddressableWord Size;               /* Size of the data chunk */
} Data;

typedef struct _WavFileHeader {
    Header Header;
    Format Format;
    Data Data;
} WavFileHeader;

typedef struct _ProcessingInfo {
    float volume;                           /* Overall volume of both channels (0 muted, 1 unchanged) */
    float panning;                          /* Channel levels relative to each other (-1 panned completely left, 1 panned completely right) */
    float phase_offset;                     /* Phase offset between channels (-1 left channel leading, 1 right channel leading) */
} ProcessingInfo;

#endif /* WAV_TYPES_H */
