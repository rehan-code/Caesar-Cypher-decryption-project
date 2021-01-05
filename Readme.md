Author: Rehan Nagoor Mohideen

Header File: A3header.h

Main Program:
  frequency_table.c:
    Description: Main function that takes in a text from a file or standard input and prints out the
                 no. of letters and characters and number of each alphabet in the file to standard output.
    Flags:
      -F "Input file name": To provide the input file name for the program. If missing takes input from standard input.

  decode.c:
    Description: Main function that takes in text and print out the decoded text.
    Flags:
      -F "Input file name": To provide the input file name for the program. If missing takes input from standard input.
      -O "Output file name": To provide the output file name for the program. If missing gives output to standard output.
      -n : Suppresses the printing of the decoded file to stdout. Useful in combination with -s or -S. If -O is included
           as a command line argument -n does nothing.
      -s : Computes the Caesar shift value used to decode the message, and prints it to stdout(e.g. decode shift = 4).
      -S : Computes the original Caesar shift value used to encode the message, and prints it to stdout(e.g. encode shift = 4).
      -t : Computes the character/lettercount summary and frequency table and prints them to stdout.
      -x : Computes the chi squared value for all shifts, printing them out along with their corresponding shift values.

  copyrecords.c:
    Description: Main function that takes in binary file and copies it to another file with the decoded text.
    Flags:
      -F "Input file name": To provide the input file name for the program. If missing takes input from standard input.
      -O "Output file name": To provide the output file name for the program. If missing gives output to standard output.
      -D "Text file name" : The name of the text file to be used to find the Caesar cipher shift to be used to decode
                            the text fields of each record. If missing, the text fields are left undecoded when copied.
      -r : Copy the records in reverse order. If missing, the records are copied in order.

    The records were reversed by finding the point where the certain data type ends by fseek and storing it in the array
    variable and moving backwards using fseek accounting for the move forward when storing the value. This is done when
    the appropriate flag is used. The variable is printed normally since the data is stored in reverse.

    As of now copyrecords does not work.

  All main programs return 0 on success.

Functions:
  letter_count:
    Declaration: int letter_count(char * string);
    in file: letter_count.c
    Description: Function to count the number of letters in a string.

  frequency_table:
    Declaration: int * frequency_table(char * string);
    in file: freq_table_function.c
    Description: Function to create the frequency table from a string.
                 Fequency table is a 16 int array that contains the number of times each letter appears in the string.

  encode:
    Declaration: int encode(char character, int shift_value);
    in file: encode.c
    Description: Function to encode a character by a shift and give out the new character after the shift.

  offset:
    Declaration: int offset(char character);
    in file: encode.c
    Description: Function produces the offset of a character from A/a. eg: offset('a') = 0 and offset('Z') = 25.

  to_decode:
    Declaration: int to_decode(int shift);
    in file: to_decode.c
    Description: Function takes a shift used to encode text and produces the shift that will decode the text.

  chi_sq:
    Declaration: double chi_sq(int shift, int * text_freq);
    in file: chi_sq.c
    Description: Function that calculates the chi-square for a given shift.

  encode_shift:
    Declaration: int encode_shift(char * string);
    in file: encode_shift.c
    Description: Function that retuens the minimum chi-square shift found from chi-sq of all shifts.
