#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "A3header.h"

/*
 *   Program name: freq_table_function.c
 *   Author: Rehan Nagoor Mohideen
 *   Student ID: 1100592
 *   Purpose: Function to create the frequency table from a string.
 */

int * frequency_table(char *string){
  int i, j;
  int *letterFreq = malloc(sizeof(int) * 26);
  if (letterFreq == NULL) { /*For error handling*/
    fprintf(stderr, "error: not enough space for malloc\n");
    exit(1);
  }

  /*To initialize all elements to 0.*/
  for (i = 0; i < 26; i++) {
   letterFreq[i] = 0;
  }
  /*To find the number of times each alphabet appears.*/
  for (i = 0; i < 26; i++) {
   for (j = 0; j < strlen(string); j++) {
     if (string[j] == 'a' + i || string[j] == 'A'+ i) {
       letterFreq[i]++;
     }
   }
  }

  return letterFreq;
}
