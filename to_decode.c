#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "A3header.h"

/*
 *   Program name: to_decode.c
 *   Author: Rehan Nagoor Mohideen
 *   Student ID: 1100592
 *   Purpose: Function takes a shift used to encode text and produces the shift that will decode the text.
 */

int to_decode(int shift){
  int newShift = shift - 2*shift;
  return newShift;
}
