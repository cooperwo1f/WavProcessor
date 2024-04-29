# WAV File Processor
Program for processing WAV file streams in real-time (based on WAV header reading project by [franciscohanna92](github.com/franciscohanna92/wav_reader.git))

## Why
I wanted to understand more about processing raw audio data and .wav files are [fairly basic](http://soundfile.sapp.org/doc/WaveFormat/).

I also wanted to be able to offset the phase between left and right channels to add on-the-fly Pro Logic and Pro Logic II
[surround encoding](https://headwizememorial.wordpress.com/2018/03/15/pro-logic-surround-decoder-principles-of-operation/).

I am building up a toolkit of lightweight audio processing and streaming tools that operate in real-time
primarily for use in music production. This is also why the input parameters have no limit checking,
as undefined behaviours often lead to interesting results.

## How to use
Clone the repository.

``` shell
git clone https://github.com/cooperwo1f/WavProcessor.git && cd WavProcessor
```

Build the project 

```shell
make all
```

Pipe data to the `WavProcessor` binary, the processed file will be printed stdout (to allow for further piping).
If `--verbose` or `-v` are present, additional information will be printed to stderr

``` shell
./build/WavProcessor < testing/test.wav #note: raw stream will be outputted to terminal
```
Or

``` shell
stream_source | ./build/WavProcessor | aplay
```

### Processing
The project supports volume, panning, and phase offset adjustments using the `--volume`, `--panning`, and `--phase-offset` parameters.

For volume, a value of 0 is equivalent to muted and a value of 1 is unchanged. Numbers above 1 are permitted but results will likely distort.
Values less than 0 are also permitted but results are undefined.

For panning, a value of -1 corresponds to a full pan to the left and 1 corresponds to a full pan to the right.
Numbers above and below those values are also permitted but the results are undefined.

For phase offset, a value of -1 offsets the right channel by 1 second (ie. left channel leading)
and a value of 1 offsets the left channel by 1 second (ie. right channel leading).
Values above and below this are also allowed but the memory usage will quickly increase as a typical file requires around 700 kB for each second.

An example of volume and panning processing on a stream can be seen below 
``` shell
./build/WavProcessor --volume=0.5 --panning=1 < ./testing/test.wav | play -q - #note: requires sox
```
