CC=gcc
CFLAGS=-lm
DEPS = wave.h wave_buffer.h
OBJ = test_wave.o wave.o wave_buffer.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
