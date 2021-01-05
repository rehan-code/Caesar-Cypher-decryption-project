all: frequency_table decode copyrecords

frequency_table: frequency_table.o freq_table_function.o letter_count.o
	gcc -ansi -Wall -o frequency_table frequency_table.o freq_table_function.o letter_count.o

frequency_table.o: frequency_table.c
	gcc -ansi -Wall -c frequency_table.c

freq_table_function.o: freq_table_function.c
	gcc -ansi -Wall -c freq_table_function.c

letter_count.o: letter_count.c
	gcc -ansi -Wall -c letter_count.c


decode: decode.o offset.o to_decode.o chi_sq.o encode_shift.o letter_count.o freq_table_function.o encode.o
	gcc -ansi -Wall -o decode decode.o offset.o to_decode.o chi_sq.o encode_shift.o letter_count.o freq_table_function.o encode.o

decode.o: decode.c
	gcc -ansi -Wall -c decode.c

encode.o: encode.c
	gcc -ansi -Wall -c encode.c

offset.o: offset.c
	gcc -ansi -Wall -c offset.c

to_decode.o: to_decode.c
	gcc -ansi -Wall -c to_decode.c

chi_sq.o: chi_sq.c
	gcc -ansi -Wall -c chi_sq.c

encode_shift.o: encode_shift.c
	gcc -ansi -Wall -c encode_shift.c

copyrecords: copyrecords.o offset.o to_decode.o chi_sq.o encode_shift.o letter_count.o freq_table_function.o encode.o
	gcc -ansi -Wall -o copyrecords copyrecords.o offset.o to_decode.o chi_sq.o encode_shift.o letter_count.o freq_table_function.o encode.o

copyrecords.o: copyrecords.c
	gcc -ansi -Wall -c copyrecords.c

clean:
	rm *.o frequency_table decode copyrecords
