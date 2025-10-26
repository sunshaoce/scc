#include "common.h"
#include <stdio.h>

static void remove_comments_in_place(char *Src) {
  char *Dst = Src;

  while (*Src) {
    // Handle single-line comment: //
    if (Src[0] == '/' && Src[1] == '/') {
      Src += 2;
      while (*Src && *Src != '\n')
        Src++;
      if (*Src == '\n')
        *Dst++ = *Src++;
    }
    // Handle multi-line comment: /* ... */
    else if (Src[0] == '/' && Src[1] == '*') {
      Src += 2;
      while (*Src && !(Src[0] == '*' && Src[1] == '/'))
        Src++;
      if (*Src) {
        Src += 2;     // Skip closing */
        *Dst++ = ' '; // Replace comment with a space
      }
    }
    // Normal character
    else {
      *Dst++ = *Src++;
    }
  }

  *Dst = '\0';
}

void preprocess(char *Src) {
  remove_comments_in_place(Src);
#ifdef DEBUG
  printf("Preprocessed Source:\n%s\n", Src);
#endif
}
