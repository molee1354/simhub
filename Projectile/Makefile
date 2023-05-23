CC = gcc
CFLAGS = -lm -I.
DEPS = projectile.h
OBJ = projectile.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o
	rm main
	rm *.out
