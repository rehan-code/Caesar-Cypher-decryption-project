#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "A3header.h"

/*
 *   Program name: encode_shift.c
 *   Author: Rehan Nagoor Mohideen
 *   Student ID: 1100592
 *   Purpose: Function that retuens the minimum chi-square shift found.
 */

int encode_shift(char *string){
  int smallestShift = 0;
  int totalLetters = letter_count(string);
  int *freqTable = frequency_table(string);
  int i;

  for (i = 1; i < 26; i++) {
    if ((chi_sq(smallestShift, freqTable) ) > (chi_sq(i, freqTable))) {
      smallestShift = i;
    }
  }

  if (chi_sq(smallestShift, freqTable) >= 0.5 && totalLetters > 200) {
    smallestShift = 0;
  }

  free(freqTable);

  return smallestShift;
}
