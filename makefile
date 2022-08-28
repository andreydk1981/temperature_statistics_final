all: prog

prog: main.o temp_functions.o
	gcc -o prog main.o temp_functions.o 

main.o: main.c temp_functions.h
	gcc -c main.c -finput-charset=utf-8 -fexec-charset=cp866

temp_functions.o: temp_functions.c temp_functions.h
	gcc -c temp_functions.c -finput-charset=utf-8 -fexec-charset=cp866
clean:
	del *.o
	del prog.exe
