CC = gcc
CFLAGS = -I.
DEPS = array.h
TEST = array.o test.o
OBJ = array.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test: $(TEST)
	$(CC) -o $@ $^ $(CFLAGS);\
	./test

clean:
	@ rm -f *.o;\
	if [ -e "main" ]; then\
		rm main;\
	fi;\
    if [ -e "test" ]; then\
		rm test;\
	fi
