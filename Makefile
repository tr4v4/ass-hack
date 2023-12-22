main: main.o assembler.o tools.o symbol_table.o
	g++ -o assembler main.o assembler.o tools.o symbol_table.o

main.o: main.c assembler.h tools.h symbol_table.h
	g++ -c main.c

assembler.o: assembler.c assembler.h tools.h
	g++ -c assembler.c

tools.o: tools.c tools.h
	g++ -c tools.c

symbol_table.o: symbol_table.c symbol_table.h
	g++ -c symbol_table.c

clean:
	rm *.o assembler