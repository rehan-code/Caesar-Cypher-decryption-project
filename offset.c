#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "A3header.h"

/*
 *   Program name: offset.c
 *   Author: Rehan Nagoor Mohideen
 *   Student ID: 1100592
 *   Purpose: Function produces the offset of a character from A/a.
 */

int offset(char character){
  int offsetVal;

  if ((character) > 64 && (character < 91)) {
   offsetVal = character - 65;

  }else if ((character > 96) && (character < 123)) {
   offsetVal = character - 97;
  }

  return offsetVal;
}
