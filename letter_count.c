#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "A3header.h"

/*
 *   Program name: letter_count.c
 *   Author: Rehan Nagoor Mohideen
 *   Student ID: 1100592
 *   Purpose: Function to count the number of letters in a string.
 */

 int letter_count(char *string){
   int i;
   int alphabetCount = 0;
   for (i = 0; i < strlen(string); i++) {
     if ((string[i] > 64 && string[i] < 91) || (string[i] > 96 && string[i] < 123)) { /*Condition to check if the character is a alphabet.*/
       alphabetCount++;
     }
   }
   return alphabetCount;
 }
