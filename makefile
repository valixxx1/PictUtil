.PHONY: all clean

all: chunk.o parsing.o main.c
	gcc chunk.o parsing.o main.c -o pict

clean:
	rm chunk.o parsing.o pict

chunk.o: chunk.c chunk.h types.h
	gcc -c -o $@ $<
parsing.o: parsing.c parsing.h chunk.h types.h
	gcc -c -o $@ $<
