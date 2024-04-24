.PHONY: all clean

OBJ = main.o logg.o bswap.o help.o imgtype.o

all: $(OBJ)
	$(CC) $(OBJ) -o pict

clean:
	rm $(OBJ) pict

main.o : main.c
	$(CC) $(CFLAGS) -c $< -o $@

logg.o : logg/logg.c
	$(CC) $(CFLAGS) -c $< -o $@

bswap.o : bswap/bswap.c
	$(CC) $(CFLAGS) -c $< -o $@

help.o : helpmenu/help.c
	$(CC) $(CFLAGS) -c $< -o $@

imgtype.o : imgtype/imgtype.c
	$(CC) $(CFLAGS) -c $< -o $@
