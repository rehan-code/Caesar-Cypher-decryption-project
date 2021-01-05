#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "A3header.h"

/*
 *   Program name: decode.c
 *   Author: Rehan Nagoor Mohideen
 *   Student ID: 1100592
 *   Purpose: main function that takes in text and print out the decoded text.
 */

int main(int argc, char *argv[]){
  int opt;
  char InputFile[100], OutputFile[100];
  int FCheck = 0, OCheck = 0, nCheck = 0, sCheck = 0, SCheck = 0, tCheck = 0, xCheck = 0;
  int encodeShift, decodeShift;
  char line;
  int noChar = 1, i;
  FILE *fp;
  char *string = malloc(sizeof(char));
  if (string == NULL) { /*For error handling*/
    fprintf(stderr, "error: not enough space for malloc\n");
    exit(1);
  }

  while ((opt = getopt(argc, argv, "F:O:nsStx")) != -1) {
    switch (opt) {
      case 'F':
        strcpy(InputFile, optarg);
        FCheck = 1;
        break;
      case 'O':
        strcpy(OutputFile, optarg);
        OCheck = 1;
        break;
      case 'n':
        nCheck = 1;
        break;
      case 's':
        sCheck = 1;
        break;
      case 'S':
        SCheck = 1;
        break;
      case 't':
        tCheck = 1;
        break;
      case 'x':
        xCheck = 1;
        break;
      case '?':
        printf("unknown option: %c\n", optopt);
        break;
    }
  }

/*To get input and take information either from file or stdin*/
  if (FCheck == 1) {
    if((fp = fopen(InputFile, "r")) != NULL ){
      if ( ((line =fgetc ( fp ))) != EOF ) {
        string[0]=line;
      }
      while ( (line =fgetc ( fp )) != EOF ) {
        string = realloc(string, sizeof(char) * ++noChar);
        if (string == NULL) { /*For error handling*/
          fprintf(stderr, "error: not enough space for realloc\n");
          exit(1);
        }
        string[noChar-1]=line;
      }
    }
    fclose(fp);
  }else {
    if ( (line =fgetc( stdin )) != EOF ) {
      string[0]=line;
    }
    while ( ((line =fgetc ( stdin ))) != EOF ) {
      string = realloc(string, sizeof(char) * ++noChar);
      if (string == NULL) { /*For error handling*/
        fprintf(stderr, "error: not enough space for realloc\n");
        exit(1);
      }
      string[noChar-1]=line;
    }
  }

  encodeShift = encode_shift(string);
  decodeShift = to_decode(encodeShift);
  int totalLetters = letter_count(string);
  char *decodedString = malloc(sizeof(char) * noChar);
  if (decodedString == NULL) { /*For error handling*/
    fprintf(stderr, "error: not enough space for malloc\n");
    exit(1);
  }

  for (i = 0; i < noChar; i++) {
    decodedString[i] = encode(string[i], decodeShift);
  }

  if (sCheck == 1) {
    printf("decode shift = %d\n\n", decodeShift);
  }

  if (SCheck == 1) {
    printf("encode shift = %d\n\n", encodeShift);
  }

  if (tCheck == 1) {
    int *freqTable = frequency_table(string);
    printf("Total no. of letter: %d, Total no. of characters: %ld\n", totalLetters, strlen(string));
    printf("Letter\tTotal no.\n");
    for (i = 0; i < 26; i++) {
      printf("%c:\t%d\n", 'A'+i, freqTable[i]);
    }
    printf("\n");
    free(freqTable);
  }

  if (xCheck == 1) {
    int *freqTable1 = frequency_table(string);
    printf("Shift\tChi_square(shift)\n");
    for (i = 0; i < 26; i++) {
      printf("%d:\t%lf\n", i, chi_sq(i, freqTable1));
    }
    printf("\n");
    free(freqTable1);
  }

/*To output information to a file or stdout if needed*/
  if (OCheck == 1) {
    if((fp = fopen(OutputFile, "w")) != NULL ){
      fprintf(fp, "%s", decodedString);
    }
    fclose(fp);
  }else if(nCheck == 0){
    printf("%s\n", decodedString);
  }

  free(string);
  free(decodedString);

  return 0;
}
