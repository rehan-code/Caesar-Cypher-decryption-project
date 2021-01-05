#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "A3header.h"

/*
 *   Program name: frequency_table.c
 *   Author: Rehan Nagoor Mohideen
 *   Student ID: 1100592
 *   Purpose: main function that takes in a text from a file or standard input and prints out the
 *            no. of letters and characters and number of each alphabet in the text.
 */

int main(int argc, char *argv[]){
  int opt;
  int *tempTable;
  int freqTable[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char FileName[100];
  FILE *fp;
  int i;
  int FCheck = 0;
  char line[1000];
  int totalLetters = 0, totalChar = 0;

  while ((opt = getopt(argc, argv, "F:")) != -1) {
    switch (opt) {
      case 'F':
        strcpy(FileName, optarg);
        FCheck = 1;
        break;
      case '?':
        printf("unknown option: %c\n", optopt);
        break;
    }
  }

  /*for (i = 0; i < argc; i++) {

    for (j = 0; j < 100; j++) {
      temp[j] = '\0';
    }
    strcpy(temp, argv[i]);

    Checking for the -F flag to take in the file name
    if (temp[0] == '-' && temp[1] == 'F') {
      if (strlen(temp) > 2) { If he entered it without space it will not go as another argument
        for (j = 2; j < strlen(temp); j++) {
          File[j-2] = temp[j];
        }

      } else {
        strcpy(File, argv[i+1]);
      }
      FCheck = 1;
    }
  }*/

  if (FCheck == 1) {
    if((fp = fopen(FileName, "r")) != NULL ){
      while ( (fgets ( line, 1000, fp )) != NULL ) {
        tempTable = frequency_table(line);
        for (i = 0; i < 26; i++) {
          freqTable[i] = freqTable[i] + tempTable[i];
        }
        free(tempTable);

        totalLetters = totalLetters + letter_count(line);
        totalChar = totalChar + strlen(line);
      }
    }
    fclose(fp);
  }else {
      while ( (fgets ( line, 1000, stdin )) != NULL ) {
        tempTable = frequency_table(line);
        for (i = 0; i < 26; i++) {
          freqTable[i] = freqTable[i] + tempTable[i];
        }
        free(tempTable);

        totalLetters = totalLetters + letter_count(line);
        totalChar = totalChar + strlen(line);
      }
  }

  printf("Total no. of letter: %d, Total no. of characters: %d\n", totalLetters, totalChar);
  printf("Letter\tTotal no.\n");
  for (i = 0; i < 26; i++) {
    printf("%c:\t%d\n", 'A'+i, freqTable[i]);
  }

  return 1;
}
