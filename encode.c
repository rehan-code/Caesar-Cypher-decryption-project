#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "A3header.h"

/*
 *   Program name: encode.c
 *   Author: Rehan Nagoor Mohideen
 *   Student ID: 1100592
 *   Purpose: Function to encode a character by a shift and give out the character after the shift.
 */

int encode(char character, int shiftVal){
  int newChar = character;

  if ((character) > 64 && (character < 91)) {
   newChar = character + shiftVal;
   if (newChar > 90) {
     newChar = 64 + (newChar - 90);
   }
   if (newChar < 65) {
     newChar = 91 + (newChar - 65);
   }

  }else if ((character > 96) && (character < 123)) {
   newChar = character + shiftVal;
   if (newChar > 122) {
     newChar = 96 + (newChar - 122);
   }
   if (newChar < 96) {
     newChar = 123 + (newChar - 97);
   }
  }

  return newChar;
}
