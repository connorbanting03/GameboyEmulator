build: CPU.o
	gcc CPU.o -o Emulator

CPU.o: CPU.c
	gcc -c CPU.c

clean:
	rm -f *.o Emulator