# WAV header reader
A simple C program to read WAV files header

## How to use
Clone the repository.

``` shell
git clone https://github.com/franciscohanna92/wav_reader.git
```

Build the project 

```shell
rm -r cmake-build-debug/
mkdir build
cd build/
cmake ../CMakeLists.txt
make all
```

Execute the `wav_reader` binary, passing as a argument a path to a WAV file. The content of the header will be printed in the standard output.

``` shell
./build/wav_reader resources/PCM_16bits_44100Hz_stereo.wav
```

## How it works
Following the [specification for the WAV header format](http://soundfile.sapp.org/doc/WaveFormat/), the task of reading this part of a WAV file is trivial.
It's only matter of following the bytes per section. Checkout the methods in `lib/wav_reader_methods.c`. They're pretty much self explainable.
![The Cannonical WAV file format](http://soundfile.sapp.org/doc/WaveFormat/wav-sound-format.gif)
