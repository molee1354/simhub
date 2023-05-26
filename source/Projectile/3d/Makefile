CC = gcc
CFLAGS = -lm -I.
DEPS = compute.h
OBJ = compute.o outputs.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o
	rm main
	rm *.out
