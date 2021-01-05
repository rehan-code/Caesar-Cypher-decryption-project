#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "A3header.h"

/*
 *   Program name: decode.c
 *   Author: Rehan Nagoor Mohideen
 *   Student ID: 1100592
 *   Purpose: main function that takes in binary file and copie it to another file with the decoded text.
 */

int main(int argc, char *argv[]){
  int opt;
  char InputFile[100], OutputFile[100], EncodedFile[100];
  int FCheck = 0, OCheck = 0, DCheck = 0, rCheck = 0;
  int encodeShift, decodeShift;
  char line;
  int noChar = 100, i, j;
  long currentPos, position;
  FILE *fp;
  char charTempPtr[1] = {' '};
  double dTempPtr[1];
  int intTempPtr[1] ;
  int nullPtrTracker = 0;
  char *string = malloc(sizeof(char)*100);
  if (string == NULL) { /*For error handling*/
    fprintf(stderr, "error: not enough space for malloc\n");
    exit(1);
  }

  struct record **record1 = NULL;
  int *noString1 = NULL;
  int *noString2 = NULL;

  typedef struct record{ /*Declaring the struture record*/
    char string1[24];
    double doubleValues[24];
    char string2[144];
    int intValues[12];
  }record;
  int noStructs;

  while ((opt = getopt(argc, argv, "F:O:D:r")) != -1) {/*Handling flags*/
    switch (opt) {
      case 'F':
        strcpy(InputFile, optarg);
        FCheck = 1;
        break;
      case 'O':
        strcpy(OutputFile, optarg);
        OCheck = 1;
        break;
      case 'D':
      strcpy(EncodedFile, optarg);
        DCheck = 1;
        break;
      case 'r':
        rCheck = 1;
        break;
      case '?':
        printf("unknown option: %c\n", optopt);
        break;
    }
  }


  if (FCheck == 1) {
    /*code for when input file is present. Open and read file.*/
    if((fp = fopen(InputFile, "rb")) != NULL ){/*To find the number of structures present go through and calculate based on \0 characters.*/
      fseek(fp, 0, SEEK_END);
      currentPos = ftell(fp);
      fseek(fp, 0, SEEK_SET);
      position = ftell(fp);
      while (position < currentPos) {
        position = ftell(fp);
        *charTempPtr = ' ';
        while (*charTempPtr != '\0' && position < currentPos){
          fread(charTempPtr, sizeof(char), 1, fp);
          /*printf("%c\n", charTempPtr[0]);*/
        }
        nullPtrTracker++;
        fseek(fp, sizeof(char)*12, SEEK_CUR);
        fseek(fp, sizeof(double)*24, SEEK_CUR);
        *charTempPtr = ' ';
        position = ftell(fp);
        while (*charTempPtr != '\0' && position < currentPos){
          fread(charTempPtr, sizeof(char), 1, fp);
          /*printf("%c\n", charTempPtr[0]);*/
        }
        nullPtrTracker++;
        fseek(fp, sizeof(char)*103, SEEK_CUR);
        fseek(fp, sizeof(int)*12, SEEK_CUR);
      }

      nullPtrTracker = nullPtrTracker - 2;
      noStructs = nullPtrTracker / 2;

      /*mallocing based on the no of structs present in the file*/
      record1 = malloc(sizeof(struct record *) * noStructs);
      for (i = 0; i < noStructs; i++) {
        record1[i] = malloc(sizeof(struct record));
      }
      noString1 = malloc(sizeof(int) * noStructs);
      noString2 = malloc(sizeof(int) * noStructs);

      fseek(fp, 0, SEEK_SET);
      for (j = 0; j < noStructs; j++) {/*To store the data in structures*/
        fread(record1[j]->string1, sizeof(char), 24, fp);
        fread(record1[j]->doubleValues, sizeof(double), 24, fp);
        fread(record1[j]->string2, sizeof(char), 144, fp);
        fread(record1[j]->intValues , sizeof(int), 12, fp);
      }
    } else {/*Error handling.*/
      fprintf(stderr, "Unable to open %s\n", InputFile);
      exit(1);
    }
    fclose(fp);
  }else{/*To get file from stdin*/
    freopen(NULL, "rb", stdin);
    fseek(stdin, 0, SEEK_END);
    currentPos = ftell(stdin);
    fseek(stdin, 0, SEEK_SET);
    position = ftell(stdin);
    while (position < currentPos) {
      position = ftell(stdin);
      *charTempPtr = ' ';
      while (*charTempPtr != '\0' && position < currentPos){
        fread(charTempPtr, sizeof(char), 1, stdin);
      }
      nullPtrTracker++;
      fseek(stdin, sizeof(char)*12, SEEK_CUR);
      fseek(stdin, sizeof(double)*24, SEEK_CUR);
      *charTempPtr = ' ';
      position = ftell(stdin);
      while (*charTempPtr != '\0' && position < currentPos){
        fread(charTempPtr, sizeof(char), 1, stdin);
      }
      nullPtrTracker++;
      fseek(stdin, sizeof(char)*103, SEEK_CUR);
      fseek(stdin, sizeof(int)*12, SEEK_CUR);
    }


    nullPtrTracker = nullPtrTracker - 2;
    noStructs = nullPtrTracker / 2;

    record1 = malloc(sizeof(struct record *) * noStructs);
    for (i = 0; i < noStructs; i++) {
      record1[i] = malloc(sizeof(struct record));
    }
    noString1 = malloc(sizeof(int) * noStructs);
    noString2 = malloc(sizeof(int) * noStructs);

    fseek(stdin, 0, SEEK_SET);

    if (rCheck == 1) {/*rflag is to store the data in reverse, to print in reverse.*/
      for (i = 0; i < noStructs; i++) {/*initializing to 0*/
        noString1[i]=0;
        noString2[i]=0;
      }
      for (j = 0; j < noStructs; j++){
        charTempPtr[0] = ' ';
        noString1[j] = 0;
        for (i = 0; *charTempPtr != '\0' && i<24; i++) {/*To find the number of characters present*/
          fread(charTempPtr, sizeof(char), 1, stdin);
          noString1[j]++;
        }
        noString1[j]--;

        *charTempPtr = ' ';
        fseek(stdin, sizeof(char)*-1, SEEK_CUR);
        for (i = 0; i < noString1[j]; i++) {/*Store the data for string1 in reverse*/
          fread(charTempPtr, sizeof(char), 1, stdin);
          record1[j]->string1[i] = *charTempPtr;
          fseek(stdin, sizeof(char)*-1, SEEK_CUR);
          fseek(stdin, sizeof(char)*-1, SEEK_CUR);
        }
        record1[j]->string1[i+1] = '\0';


        fseek(stdin, sizeof(char)*25, SEEK_SET);
        for (i = 0; i < 24; i++) {/*To store the data for the double in reverse*/
          fread(dTempPtr, sizeof(double), 1, stdin);
          record1[j]->doubleValues[i] = dTempPtr[0];
          fseek(stdin, sizeof(double)*-2, SEEK_CUR);
        }
        dTempPtr[0] = 0;


        fseek(stdin, sizeof(double)*25, SEEK_CUR);/*pointer now after all the double charactrs*/
        charTempPtr[0] = ' ';
        noString2[j] = 0;
        for (i = 0; *charTempPtr != '\0' && i<144; i++) {/*To find the no of character for string 2*/
          fread(charTempPtr, sizeof(char), 1, stdin);
          noString2[j]++;
        }
        noString2[j]--;
        *charTempPtr = ' ';

        fseek(stdin, sizeof(char)*-1, SEEK_CUR);
        for (i = 0; i < noString2[j]; i++) {/*Store string 2 in reverse*/
          fread(charTempPtr, sizeof(char), 1, stdin);
          record1[j]->string2[i] = *charTempPtr;
          fseek(stdin, sizeof(char)*-1, SEEK_CUR);
          fseek(stdin, sizeof(char)*-1, SEEK_CUR);
        }
        record1[j]->string2[i+1] = '\0';


        fseek(stdin, sizeof(char)*145, SEEK_CUR);
        for (i = 0; i < 12; i++) {/*Store the in values in reverse.*/
          fread(intTempPtr, sizeof(int), 1, stdin);
          record1[j]->intValues[i] = intTempPtr[0];
          fseek(stdin, sizeof(int)*-2, SEEK_CUR);
        }
        intTempPtr[0] = 0;

        fseek(stdin, sizeof(int)*13, SEEK_CUR);
      }
    }else{/*Take in normally from stdin*/

      for (j = 0; j < noStructs; j++) {
        fread(record1[j]->string1, sizeof(char), 24, stdin);

        fread(record1[j]->doubleValues, sizeof(double), 24, stdin);

        fread(record1[j]->string2, sizeof(char), 144, stdin);

        fread(record1[j]->intValues , sizeof(int), 12, stdin);
      }
    }
  }


  /*To get input and find the decrypt key either from file*/
    if (DCheck == 1) {
      if((fp = fopen(EncodedFile, "r")) != NULL ){
        if ( (fgets(string, 100, fp)) != NULL ) {
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

      encodeShift = encode_shift(string);
      decodeShift = to_decode(encodeShift);/*obtain decryption shift*/

      for (j = 0; j < noStructs; j++) {/*To decrypt string 1 and 2 and store it decrypted.*/
        for (i = 0; record1[j]->string1[i] != '\0'; i++) {
          record1[j]->string1[i] = encode(record1[j]->string1[i], decodeShift);
        }

        for (i = 0; record1[j]->string2[i] != '\0'; i++) {
          record1[j]->string2[i] = encode(record1[j]->string2[i], decodeShift);
        }
      }
    }


/*To output information to a file or stdout if needed*/
  if (OCheck == 1) {/*To output to a file*/
    if((fp = fopen(OutputFile, "wb")) != NULL ){
      if (rCheck == 1 && FCheck == 0) {/*To check if output needs to be reversed*/
        for (j = 0; j < noStructs; j++) {
          fwrite(record1[j]->intValues, sizeof(int), 12, fp);
          fwrite(record1[j]->string2, sizeof(char), 144, fp);
          fwrite(record1[j]->doubleValues, sizeof(double), 24, fp);
          fwrite(record1[j]->string1, sizeof(char), 24, fp);
        }
      }else{
        for (j = 0; j < noStructs; j++) {
          fwrite(record1[j]->string1, sizeof(char), 24, fp);
          fwrite(record1[j]->doubleValues, sizeof(double), 24, fp);
          fwrite(record1[j]->string2, sizeof(char), 144, fp);
          fwrite(record1[j]->intValues, sizeof(int), 12, fp);
        }
      }
    }
    fclose(fp);
  }else {/*Output to stdout*/
    if (rCheck == 1 && FCheck == 0) {
      for (j = 0; j < noStructs; j++) {
        fwrite(record1[j]->intValues, sizeof(int), 12, stdout);
        fwrite(record1[j]->string2, sizeof(char), 144, stdout);
        fwrite(record1[j]->doubleValues, sizeof(double), 24, stdout);
        fwrite(record1[j]->string1, sizeof(char), 24, stdout);
      }
    }else{
      for (j = 0; j < noStructs; j++) {
        fwrite(record1[j]->string1, sizeof(char), 24, stdout);
        fwrite(record1[j]->doubleValues, sizeof(double), 24, stdout);
        fwrite(record1[j]->string2, sizeof(char), 144, stdout);
        fwrite(record1[j]->intValues, sizeof(int), 12, stdout);
      }
    }
  }

  /*free all malloced variables*/
  free(string);
  for (i = 0; i < noStructs; i++) {
    free(record1[i]);
  }
  free(record1);
  free(noString1);
  free(noString2);

  return 0;
}
