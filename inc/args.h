#ifndef ARGS_H
#define ARGS_H

#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STRING_WITH_SIZE(str) str, sizeof(str)-1

typedef struct {

  // Define custom argument structure here
  unsigned char verbose: 1;

  float volume;
  float panning;
  float phase_offset;

} Arguments;

Arguments parse_arguments(int argc, char** argv) {
  Arguments args;
  memset((void*)&args, 0, sizeof(args));
  args.volume = 1.0;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == '-') {

        // Add further argument definitions here
        if (strcmp(argv[i], "--verbose") == 0) { args.verbose = 1; }

        if (strncmp(argv[i], STRING_WITH_SIZE("--volume")) == 0) {
            if (argv[i][sizeof("--volume") - 1] != '=') { fprintf(stderr, "MISSING '=' after --volume\n"); }
            strsep(&argv[i], "=");
            args.volume = strtof(argv[i], NULL);
        }

        if (strncmp(argv[i], STRING_WITH_SIZE("--panning")) == 0) {
            if (argv[i][sizeof("--panning") - 1] != '=') { fprintf(stderr, "MISSING '=' after --panning\n"); }
            strsep(&argv[i], "=");
            args.panning = strtof(argv[i], NULL);
        }

        if (strncmp(argv[i], STRING_WITH_SIZE("--phase-offset")) == 0) {
            if (argv[i][sizeof("--phase-offset") - 1] != '=') { fprintf(stderr, "MISSING '=' after --phase-offset\n"); }
            strsep(&argv[i], "=");
            args.phase_offset = strtof(argv[i], NULL);
        }

      }
      else {
        for (size_t j = 1; j < strlen(argv[i]); j++) {

          // Add further argument definitions here
          if (argv[i][j] == 'v') { args.verbose = 1; }

        }
      }
    }
  }

  return args;
}

#ifdef __cplusplus
}
#endif

#endif /* ARGS_H */
