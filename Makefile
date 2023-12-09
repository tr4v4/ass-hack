main: main.o assembler.o tools.o
	g++ -o a.out main.o assembler.o tools.o

main.o: main.c assembler.h tools.h
	g++ -c main.c

assembler.o: assembler.c assembler.h tools.h
	g++ -c assembler.c

tools.o: tools.c tools.h
	g++ -c tools.c

clean:
	rm *.o