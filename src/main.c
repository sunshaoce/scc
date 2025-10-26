#include "common.h"
#include <stdio.h>
#include <stdlib.h>

static void parse_args(int Argc, const char **Argv, const char **ProgName,
                       const char **SrcFile, const char **OutputFile) {
  *ProgName = Argv[0];

  for (int I = 1; I < Argc; ++I) {
    if (Argv[I][0] == '-') {
      if (Argv[I][1] == 'o') {
        // Handle output file option
        ++I; // Skip next argument as it is the output file name
        *OutputFile = Argv[I];
        continue;
      }
    } else {
      *SrcFile = Argv[I];
      continue;
    }
  }
}

char *read_file(const char *FileName) {
  FILE *FP = fopen(FileName, "rb");
  if (!FP) {
    perror("fopen");
    exit(1);
  }

  // Move to end to get file size
  fseek(FP, 0, SEEK_END);
  long FileSize = ftell(FP);
  rewind(FP);

  // Allocate memory (+1 for null terminator)
  char *Buffer = malloc(FileSize + 1);
  if (!Buffer) {
    fprintf(stderr, "Error: Memory allocation failed\n");
    fclose(FP);
    exit(1);
  }

  // Read file contents
  fread(Buffer, 1, FileSize, FP);
  Buffer[FileSize] = '\0';

  fclose(FP);
  return Buffer;
}

int main(int Argc, const char **Argv) {
  const char *ProgName = "scc";
  const char *InFile = NULL;
  const char *OutFile = "a.out";

  parse_args(Argc, Argv, &ProgName, &InFile, &OutFile);

#ifdef DEBUG
  printf("Program: %s\n", ProgName);
  printf("InputFile: %s\n", InFile);
  printf("OutputFile: %s\n", OutFile);
#endif

  char *Contents = read_file(InFile);

#ifdef DEBUG
  printf("File Contents:\n%s\n", Contents);
#endif

  preprocess(Contents);

  return 0;
}
