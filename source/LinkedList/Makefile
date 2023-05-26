CC = gcc
CFLAGS = -I.
DEPS = linkedlist.h
OBJ = linkedlist.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o
	rm main
