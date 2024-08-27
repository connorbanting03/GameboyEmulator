build: CPU.o
	gcc CPU.o -o Emulator

test_gameboy: test_gameboy.o CPU.o
	gcc CPU.o test_gameboy.o -o test_gameboy

CPU.o: CPU.c CPU.h
	gcc -c CPU.c CPU.h

test_gameboy.o: test_gameboy.c 
	gcc -c test_gameboy.c

clean:
	rm -f *.o Emulator test_gameboy