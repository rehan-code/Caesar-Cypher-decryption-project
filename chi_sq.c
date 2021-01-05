#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "A3header.h"

/*
 *   Program name: chi_sq.c
 *   Author: Rehan Nagoor Mohideen
 *   Student ID: 1100592
 *   Purpose: Function that calculates chi square for a given shift.
 */

double chi_sq(int shift, int *text_freq){
  int totalLetters = 0;
  const double EF[26] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07707 , 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074};
  double chiVal = 0.0;
  int i;

  for (i = 0; i < 26; i++) {
    totalLetters += text_freq[i];
  }

  for (i = 0; i < 26; i++) {

    chiVal = chiVal + ((( totalLetters * EF[offset('a'+i)] - text_freq[offset(encode('a'+i, shift))] ) * ( totalLetters * EF[offset('a'+i)] - text_freq[offset(encode('a'+i, shift))] ) ) / (totalLetters * totalLetters * EF[offset('a'+i)]));
  }
  return chiVal;
}
